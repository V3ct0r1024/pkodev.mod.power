#include <windows.h>
#include <detours.h>

#include <vector>
#include <string>
#include <fstream>

#include "hook.h"
#include "pointer.h"
#include "structure.h"

#include "..\loader\loader.h"


namespace pkodev
{
    namespace utils
    {
        // Trim a string
        std::string trim(const std::string& str, const std::string& whitespace = " \t");

        // Replace all substrings to another one in a string
        std::string replace(std::string subject, const std::string& search,
            const std::string& replace);
    }

    namespace global
    {
        // Characters power list on the game scene
        std::vector<pkodev::Power> scene;

        // Power label format
        std::string label{ "" };
    }
}

// Get power label format
std::string get_label_format(const std::string& cfg_path);

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
    strcpy_s(info.name, TOSTRING(MOD_NAME));
    strcpy_s(info.version, TOSTRING(MOD_VERSION));
    strcpy_s(info.author, TOSTRING(MOD_AUTHOR));
    info.exe_version = MOD_EXE_VERSION;
}

// Start the mod
void Start(const char* path)
{
    // Build path to config file
    char buf[MAX_PATH]{ 0x00 };
    std::snprintf(buf, sizeof(buf), "%s\\%s.cfg", path, TOSTRING(MOD_NAME));

    // Get power label format
    pkodev::global::label = get_label_format(buf);

    // Reserve some memory
    pkodev::global::scene.reserve(64);

    // Enable hooks
    DetourRestoreAfterWith();
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)pkodev::pointer::ReadChaAttrPacket, pkodev::hook::ReadChaAttrPacket);
    DetourAttach(&(PVOID&)pkodev::pointer::NetActorDestroy, pkodev::hook::NetActorDestroy);
    DetourAttach(&(PVOID&)pkodev::pointer::CHeadSay__Render, pkodev::hook::CHeadSay__Render);
    DetourTransactionCommit();
}

// Stop the mod
void Stop()
{
    // Disable hooks
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&(PVOID&)pkodev::pointer::ReadChaAttrPacket, pkodev::hook::ReadChaAttrPacket);
    DetourDetach(&(PVOID&)pkodev::pointer::NetActorDestroy, pkodev::hook::NetActorDestroy);
    DetourDetach(&(PVOID&)pkodev::pointer::CHeadSay__Render, pkodev::hook::CHeadSay__Render);
    DetourTransactionCommit();
}

// void ReadChaAttrPacket(LPRPACKET pk, stNetChaAttr &SChaAttr, char* szLogName)
void __cdecl pkodev::hook::ReadChaAttrPacket(void* pk, void* SChaAttr, 
    char* szLogName)
{
    // Call original function ReadChaAttrPacket()
    pkodev::pointer::ReadChaAttrPacket(pk, SChaAttr, szLogName);

    // Read syncronization packet
    unsigned int cha_id = static_cast<unsigned int>(pkodev::pointer::RPacket__ReadLong(pk));
    unsigned int power  = static_cast<unsigned int>(pkodev::pointer::RPacket__ReadLong(pk));
    unsigned int color  = static_cast<unsigned int>(pkodev::pointer::RPacket__ReadLong(pk));

    // Check character ID
    if (cha_id == 0)
    {
        // It is a monster
        return;
    }

    // Search character on the world scene
    auto cha = std::find_if(
        pkodev::global::scene.begin(),
        pkodev::global::scene.end(),
        [&cha_id](const pkodev::Power& p)
        {
            return (p.world_id == cha_id);
        }
    );

    // Check that character is found
    if ( cha != pkodev::global::scene.end() )
    {
        // Update character
        cha->power = power;
        cha->color = color;
    }
    else
    {
        // Insert character to the list
        pkodev::global::scene.push_back({ cha_id, power, color });
    }
}

// void NetActorDestroy(unsigned int nID, char chSeeType)
void __cdecl pkodev::hook::NetActorDestroy(unsigned int nID, char chSeeType)
{
    // Get pointer to character
    pkodev::Character* cha = reinterpret_cast<pkodev::Character*>(
        pkodev::pointer::CGameScene__SearchByID(
            reinterpret_cast<void*>(
                *reinterpret_cast<unsigned int*>(
                    pkodev::address::MOD_EXE_VERSION::CGameApp___pCurScene
                )
            ),
            nID
        )
    );
    
    // Check pointer
    if (cha != nullptr)
    {
        // Check that is it a player
        if (cha->type == 1)
        {
            // Remove character from power list
            pkodev::global::scene.erase(
                std::remove_if(
                    pkodev::global::scene.begin(),
                    pkodev::global::scene.end(),
                    [&nID](const pkodev::Power& p)
                    {
                        return (p.world_id == nID);
                    }
                ),
                pkodev::global::scene.end()
            );
        }
    }

    // Call original function
    pkodev::pointer::NetActorDestroy(nID, chSeeType);
}

// void CHeadSay::Render(D3DXVECTOR3& pos)
void __fastcall pkodev::hook::CHeadSay__Render(void* This, void* NotUsed, D3DXVECTOR3& Pos)
{
    // Call original function
    pkodev::pointer::CHeadSay__Render(This, Pos);

    // Is the display of the character's name enabled?
    bool bShowName = static_cast<bool>(
        *reinterpret_cast<char*>(
            reinterpret_cast<unsigned int>(This) + 0x49
        )
    );

    // Do not render power amount if the display is disabled
    if (bShowName == false)
    {
        // Exit the hook
        return;
    }
    
    // Get current character data
    pkodev::Character* cha = reinterpret_cast<pkodev::Character*>(
        *reinterpret_cast<unsigned int*>(
            reinterpret_cast<unsigned int>(This) + 0x28
        )
    );

    // Check that character is a player character
    if (cha->type != 1)
    {
        // Exit the hook
        return;
    }

    // Search current character on the scene
    auto cha_scene = std::find_if(
        pkodev::global::scene.begin(),
        pkodev::global::scene.end(),
        [&cha](const pkodev::Power& p) 
        {
            return (p.world_id == cha->cha_id);
        }
    );

    // Check that character is found
    if ( cha_scene == pkodev::global::scene.end() )
    {
        // Exit the hook
        return;
    }

    // Build power amount string
    char buf[32]{ 0x00 };
    std::snprintf(buf, sizeof(buf), pkodev::global::label.c_str(), cha_scene->power);

    // Power text label position
    int x = 0;
    int y = 0;

    // Get label position
    pkodev::pointer::MPRender__WorldToScreen(
        reinterpret_cast<void*>(
            *reinterpret_cast<unsigned int*>(
                pkodev::address::MOD_EXE_VERSION::MPRender
            )
        ),
        Pos.x,
        Pos.y,
        Pos.z + cha->Info->height,
        &x,
        &y
    );

    // Chack that character is a party leader
    if (cha->cha_id == cha->party_id)
    {
        // Increase the y coordinate by 20 units
        y -= 20;
    }

    // Check that the character is flying
    if (pkodev::pointer::CCharacter__GetIsFly(cha) == true)
    {
        // Increase the y coordinate by 30 units
        y -= 30;
    }

    // Check that character is a guild member
    if (cha->guild_id != 0)
    {
        // Increase the y coordinate by 14 units
        y -= 14;
    }

    // Check that the character is trading in set stall
    if ( static_cast<int>((*((char*)&(cha->cha_state) + 1)) & 2) == 0 )
    {
        // Increase the y coordinate by 34 units
        y -= 34;
    }

    // Get label text size
    tagSIZE size{ 0x00 };
    pkodev::pointer::CMPFont__GetTextSize
    (
        reinterpret_cast<void*>(
            *reinterpret_cast<unsigned int*>(
                pkodev::address::MOD_EXE_VERSION::CMPFont
            )
        ),
        const_cast<char*>(buf),
        &size,
        1.0f
    );

    // Aligning the coordinates
    x = x - size.cx / 2;
    y = y - 24;

    // Draw the text label with power amount
    pkodev::pointer::CGuiFont_BRender(
        reinterpret_cast<void*>(pkodev::address::MOD_EXE_VERSION::CGuiFont),
        buf,
        x,
        y,
        cha_scene->color,
        0xFF000000
    );
}

// Get power label string format
std::string get_label_format(const std::string& cfg_path)
{
    // Placeholder
    const std::string _placeholder{ "{:power:}" };

    // The resulting string
    std::string str{ _placeholder };


    // Open the .cfg file
    std::ifstream file(cfg_path, std::ifstream::in);

    // Check that file is open
    if (file.is_open() == true)
    {
        // Read a line
        std::getline(file, str);

        // Trim the line and remove special chars
        str = pkodev::utils::replace(
            pkodev::utils::trim(str), 
            "%", 
            "%%"
        );

        // Close the file
        file.close();
    }

    // Search the placeholder
    const std::size_t pos = str.find_first_of(_placeholder);

    // Check that the placeholder is found
    if (pos != std::string::npos)
    {
        // Replace placeholder with %d
        str.replace(pos, _placeholder.length(), "%d");
    }

    return str;
}

// Trim a string
std::string pkodev::utils::trim(const std::string& str, const std::string& whitespace)
{
    // Left trim
    auto ltrim = [](const std::string& str, const std::string& whitespace) -> std::string
    {
        // Looking for whitespaces at the beginning of a string
        const std::size_t pos = str.find_first_not_of(whitespace);

        // Remove spaces at the beginning of a string
        if (std::string::npos != pos)
        {
            return str.substr(pos);
        }

        return "";
    };

    // Right trim
    auto rtrim = [](const std::string& str, const std::string& whitespace) -> std::string
    {
        // Looking for whitespaces at the end of a string
        const std::size_t pos = str.find_last_not_of(whitespace);

        // Remove spaces at the end of a string
        if (std::string::npos != pos)
        {
            return str.substr(0, pos + 1);
        }

        return "";
    };

    return ltrim(rtrim(str, whitespace), whitespace);
}

// Replace all substrings to another one in a string
std::string pkodev::utils::replace(std::string subject, const std::string& search,
    const std::string& replace)
{
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}