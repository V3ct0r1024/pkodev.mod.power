#include <windows.h>
#include <detours.h>

#include <iostream>

#include "pointer.h"
#include "hook.h"
#include "structure.h"

#include "..\loader\loader.h"

/*
*    Add this function to file functions.lua: 
*       function CalculatePower(role)
*           
*           return 0, 4294967295 -- (power, color)
* 
*       end
* 
* 
*    Execute this SQL-query in MSSQL ServerManagement Studio:
*       USE GameDB
*       ALTER TABLE character ADD power INT NOT NULL DEFAULT (0)
*/

// Calculate player's character power amount
pkodev::Power CalcPlayerPower(void* role);

// Get character ID
unsigned int GetRoleID(void* role);

// Get main character
void* GetMainCha(void* role);

// Write power data to the synchronization packet
void WriteSyncPacket(void* role, void* packet, short int sSynType);

// Entry point
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    // Nothing to do . . .
    return TRUE;
}

// Get mod information
void GetModInformation(mod_info& info)
{
    strcpy_s(info.name,    TOSTRING(MOD_NAME));
    strcpy_s(info.version, TOSTRING(MOD_VERSION));
    strcpy_s(info.author,  TOSTRING(MOD_AUTHOR));
    info.exe_version = MOD_EXE_VERSION;
}

// Start the mod
void Start(const char* path)
{
    // Enable hooks
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)pkodev::pointer::CFightAble__WriteAttr, pkodev::hook::CFightAble__WriteAttr);
    DetourAttach(&(PVOID&)pkodev::pointer::CFightAble__WriteAttrEx, pkodev::hook::CFightAble__WriteAttrEx);
    DetourAttach(&(PVOID&)pkodev::pointer::CFightAble__WriteMonsAttr, pkodev::hook::CFightAble__WriteMonsAttr);
    DetourAttach(&(PVOID&)pkodev::pointer::CFightAble__SynAttrToSelf, pkodev::hook::CFightAble__SynAttrToSelf);
    DetourAttach(&(PVOID&)pkodev::pointer::CTableCha__SaveAllData, pkodev::hook::CTableCha__SaveAllData);
    DetourTransactionCommit();

    // Write welcome message
    std::cout << "[" << TOSTRING(MOD_NAME) << "] Power system ver. " << TOSTRING(MOD_VERSION) << " by " << TOSTRING(MOD_AUTHOR) << std::endl;
}

// Stop the mod
void Stop()
{
    // Disable hooks
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&(PVOID&)pkodev::pointer::CFightAble__WriteAttr, pkodev::hook::CFightAble__WriteAttr);
    DetourDetach(&(PVOID&)pkodev::pointer::CFightAble__WriteAttrEx, pkodev::hook::CFightAble__WriteAttrEx);
    DetourDetach(&(PVOID&)pkodev::pointer::CFightAble__WriteMonsAttr, pkodev::hook::CFightAble__WriteMonsAttr);
    DetourDetach(&(PVOID&)pkodev::pointer::CFightAble__SynAttrToSelf, pkodev::hook::CFightAble__SynAttrToSelf);
    DetourDetach(&(PVOID&)pkodev::pointer::CTableCha__SaveAllData, pkodev::hook::CTableCha__SaveAllData);
    DetourTransactionCommit();
}

// Calculate player's character power amount
pkodev::Power CalcPlayerPower(void* role)
{
    // Get pointer to player's main character
    void* pMainCha = GetMainCha(role);

    // Check that role is a player's character
    if (pMainCha == nullptr)
    {
        // It is a monster
        return pkodev::Power(0, 0);
    }

    // Call user-defined LUA function
    int ret = pkodev::pointer::CParser__DoString(
        reinterpret_cast<void*>(pkodev::address::MOD_EXE_VERSION::CParser),
        "CalculatePower", 
        pkodev::enumSCRIPT_RETURN_NUMBER, 
        2, 
        pkodev::enumSCRIPT_PARAM_LIGHTUSERDATA,
        1, 
        pMainCha,
        pkodev::DOSTRING_PARAM_END
    );

    // Check result
    if (ret != 0)
    {
        // Get power amount
        unsigned int power = static_cast<unsigned int>(
            pkodev::pointer::CParser__GetReturnNumber(
                reinterpret_cast<void*>(pkodev::address::MOD_EXE_VERSION::CParser),
                0
            )
        );

        // Get power color
        unsigned int color = static_cast<unsigned int>(
            pkodev::pointer::CParser__GetReturnNumber(
                reinterpret_cast<void*>(pkodev::address::MOD_EXE_VERSION::CParser),
                1
            )
        );

        // Return power amount and color
        return pkodev::Power(power, color);
    }

    // Return power and color by default (power: 0; color: whilte [0xFFFFFFFF])
    return pkodev::Power(0, 0xFFFFFFFF);
}

// Get character ID
unsigned int GetRoleID(void* role)
{
    // Get pointer to CAttachable::m_pCPlayer
    void* pPlayer = reinterpret_cast<void*>(
        *reinterpret_cast<unsigned int*>(
            reinterpret_cast<unsigned int>(role) + 0x21C
        )
    );

    // Check that role is a player's character
    if (pPlayer == nullptr)
    {
        // It is a monster, ID = 0
        return 0;
    }

    // Return character's ID
    return *reinterpret_cast<unsigned int*>(
        reinterpret_cast<unsigned int>(pPlayer) + 0xFE8
    );
}

// Get player's main character
void* GetMainCha(void* role)
{
    // Get pointer to CAttachable::m_pCPlayer
    void* pPlayer = reinterpret_cast<void*>(
        *reinterpret_cast<unsigned int*>(
            reinterpret_cast<unsigned int>(role) + 0x21C
        )
    );

    // Check that role is a player's character
    if (pPlayer == nullptr)
    {
        // It is a monster, no main character
        return nullptr;
    }

    // Return pointer to main player's character
    return reinterpret_cast<void *>(
        *reinterpret_cast<unsigned int*>(
            reinterpret_cast<unsigned int>(pPlayer) + 0x1078
        )
   );
}

// Write power data to the synchronization packet
void WriteSyncPacket(void* role, void* packet, short int sSynType)
{
    // Check the synchronize type
    if (sSynType != 3)
    {
        // Get power data
        pkodev::Power calc = CalcPlayerPower(role);

        // Write packet
        pkodev::pointer::WPacket__WriteLong(packet, GetRoleID(role)); // Character ID
        pkodev::pointer::WPacket__WriteLong(packet, calc.power);      // Power amount
        pkodev::pointer::WPacket__WriteLong(packet, calc.color);      // Power color
    }
}

// void CFightAble::WriteAttr(WPACKET & pk, Short sSynType)
void __fastcall pkodev::hook::CFightAble__WriteAttr(void* This, void* NotUsed,
    void* pk, short int sSynType)
{
    // Call original function CFightAble::WriteAttr()
    pkodev::pointer::CFightAble__WriteAttr(This, pk, sSynType);

    // Write packet
    WriteSyncPacket(This, pk, sSynType);
}

// void	CFightAble::WriteAttr(WPACKET &pk, dbc::Short sStartAttr, dbc::Short sEndAttr, dbc::Short sSynType)
void __fastcall pkodev::hook::CFightAble__WriteAttrEx(void* This, void* NotUsed,
    void* pk, short int sStartAttr, short int sEndAttr, short int sSynType)
{
    // Call original function CFightAble::WriteAttr()
    pkodev::pointer::CFightAble__WriteAttrEx(This, pk, sStartAttr, sEndAttr, sSynType);

    // Write packet
    WriteSyncPacket(This, pk, sSynType);
}

// void CFightAble::WriteMonsAttr(WPACKET &pk, Short sSynType)
void __fastcall pkodev::hook::CFightAble__WriteMonsAttr(void* This, void* NotUsed, 
    void* pk, short int sSynType)
{
    // Call original function CFightAble::WriteMonsAttr()
    pkodev::pointer::CFightAble__WriteMonsAttr(This, pk, sSynType);

    // Write packet
    WriteSyncPacket(This, pk, sSynType);
}

// void CFightAble::SynAttrToSelf(Short sType)
void __fastcall pkodev::hook::CFightAble__SynAttrToSelf(void* This, 
    void* NotUsed, short int sSynType)
{
    // Call function CFightAble::SynAttr() instead of CFightAble::SynAttrToSelf()
    pkodev::pointer::CFightAble__SynAttr(This, sSynType);
}

// bool CTableCha::SaveAllData(CPlayer* pPlayer, char chSaveType)
bool __fastcall pkodev::hook::CTableCha__SaveAllData(void* This, void* NotUsed,
    void* pPlayer, char chSaveType)
{
    // Call original function CTableCha::SaveAllData()
    bool ret = pkodev::pointer::CTableCha__SaveAllData(This, pPlayer, chSaveType);

    // Save character power in GameDB.dbo.Character
    if (ret == true)
    {
        // Get character
        void* cha = reinterpret_cast<void*>(
            *reinterpret_cast<unsigned int*>(
                reinterpret_cast<unsigned int>(pPlayer) + 0x1078
            )
        );
        
        // Buffer for SQL-query
        char sql[128]{ 0x00 };

        // Build SQL query
        sprintf_s(
            sql, 
            sizeof(sql), 
            "UPDATE %s SET power = %d WHERE cha_id = %d", 
            pkodev::pointer::cfl_rs___get_table(This),
            CalcPlayerPower(cha).power,
            GetRoleID(cha)
        );

        // Trying execute the query
        pkodev::pointer::cfl_rs__exec_sql_direct(This, sql, 5);
    }

    return ret;
}