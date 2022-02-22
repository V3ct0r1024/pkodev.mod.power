#pragma once
#include "address.h"

namespace pkodev
{
	namespace pointer
	{
		// void CFightAble::WriteAttr(WPACKET & pk, Short sSynType)
		typedef void(__thiscall* CFightAble__WriteAttr__Ptr)(void*, void*, short int);
		CFightAble__WriteAttr__Ptr CFightAble__WriteAttr = (CFightAble__WriteAttr__Ptr)(void*)(address::MOD_EXE_VERSION::CFightAble_WriteAttr);
		
		// void	CFightAble::WriteAttr(WPACKET &pk, dbc::Short sStartAttr, dbc::Short sEndAttr, dbc::Short sSynType)
		typedef void(__thiscall* CFightAble__WriteAttrEx__Ptr)(void*, void*, short int, short int, short int);
		CFightAble__WriteAttrEx__Ptr CFightAble__WriteAttrEx = (CFightAble__WriteAttrEx__Ptr)(void*)(address::MOD_EXE_VERSION::CFightAble__WriteAttrEx);

		// void CFightAble::WriteMonsAttr(WPACKET &pk, Short sSynType)
		typedef void(__thiscall* CFightAble__WriteMonsAttr__Ptr)(void*, void*, short int);
		CFightAble__WriteMonsAttr__Ptr CFightAble__WriteMonsAttr = (CFightAble__WriteMonsAttr__Ptr)(void*)(address::MOD_EXE_VERSION::CFightAble_WriteMonsAttr);

		// void CFightAble::SynAttr(Short sType)
		typedef void(__thiscall* CFightAble__SynAttr__Ptr)(void*, short int);
		CFightAble__SynAttr__Ptr CFightAble__SynAttr = (CFightAble__SynAttr__Ptr)(void*)(address::MOD_EXE_VERSION::CFightAble_SynAttr);

		// void CFightAble::SynAttrToSelf(Short sType)
		typedef void(__thiscall* CFightAble__SynAttrToSelf__Ptr)(void*, short int);
		CFightAble__SynAttrToSelf__Ptr CFightAble__SynAttrToSelf = (CFightAble__SynAttrToSelf__Ptr)(void*)(address::MOD_EXE_VERSION::CFightAble_SynAttrToSelf);

		// int CParser::DoString(const char *csString, char chRetType, int nRetNum, ...)
		typedef int(__cdecl* CParser__DoString__Ptr)(void*, const char*, char, int, ...);
		CParser__DoString__Ptr CParser__DoString = (CParser__DoString__Ptr)(void*)(address::MOD_EXE_VERSION::CParser__DoString);
	
		// int CParser::GetReturnNumber(char chID)
		typedef int(__thiscall* CParser__GetReturnNumber__Ptr)(void*, int);
		CParser__GetReturnNumber__Ptr CParser__GetReturnNumber = (CParser__GetReturnNumber__Ptr)(void*)(address::MOD_EXE_VERSION::CParser__GetReturnNumber);

		// bool WPacket::WriteLong(uLong lo)
		typedef int(__thiscall* WPacket__WriteLong__Ptr)(void*, int);
		WPacket__WriteLong__Ptr WPacket__WriteLong = (WPacket__WriteLong__Ptr)(void*)(address::MOD_EXE_VERSION::WPacket__WriteLong);

		// bool CTableCha::SaveAllData(CPlayer* pPlayer, char chSaveType)
		typedef bool(__thiscall* CTableCha__SaveAllData__Ptr)(void*, void*, char);
		CTableCha__SaveAllData__Ptr CTableCha__SaveAllData = (CTableCha__SaveAllData__Ptr)(void*)(address::MOD_EXE_VERSION::CTableCha__SaveAllData);

		// SQLRETURN cfl_rs::exec_sql_direct(char const* sql, unsigned short timeout /* = 5 */)
		typedef short int(__thiscall* cfl_rs__exec_sql_direct__Ptr)(void*, const char*, unsigned short);
		cfl_rs__exec_sql_direct__Ptr cfl_rs__exec_sql_direct = (cfl_rs__exec_sql_direct__Ptr)(void*)(address::MOD_EXE_VERSION::cfl_rs__exec_sql_direct);
		
		// inline char const* const cfl_rs::_get_table() const
		typedef char const* const(__thiscall* cfl_rs___get_table__Ptr)(void*);
		cfl_rs___get_table__Ptr cfl_rs___get_table = (cfl_rs___get_table__Ptr)(void*)(address::MOD_EXE_VERSION::cfl_rs___get_table);
	}
}