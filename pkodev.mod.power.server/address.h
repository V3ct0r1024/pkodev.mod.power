#pragma once

namespace pkodev
{
	namespace address
	{
		// GameServer.exe 1.36
		namespace GAMESERVER_136
		{
			// void CFightAble::WriteAttr(WPACKET &pk, Short sSynType)
			const unsigned int CFightAble_WriteAttr = 0x004FCEB0;

			// void	CFightAble::WriteAttr(WPACKET &pk, dbc::Short sStartAttr, dbc::Short sEndAttr, dbc::Short sSynType)
			const unsigned int CFightAble__WriteAttrEx = 0x004FD040;

			// void CFightAble::WriteMonsAttr(WPACKET &pk, Short sSynType)
			const unsigned int CFightAble_WriteMonsAttr = 0x004FCF60;

			// void CFightAble::SynAttr(Short sType)
			const unsigned int CFightAble_SynAttr = 0x004FBE20;

			// void CFightAble::SynAttrToSelf(Short sType)
			const unsigned int CFightAble_SynAttrToSelf = 0x004FC000;

			// CParser
			const unsigned int CParser = 0x00604378;

			// int CParser::DoString(const char *csString, char chRetType, int nRetNum, ...)
			const unsigned int CParser__DoString = 0x004553D0;

			// int CParser::GetReturnNumber(char chID)
			const unsigned int CParser__GetReturnNumber = 0x00492780;

			// bool WPacket::WriteLong(uLong lo)
			const unsigned int WPacket__WriteLong = 0x0051B8B0;

			// bool CTableCha::SaveAllData(CPlayer* pPlayer, char chSaveType)
			const unsigned int CTableCha__SaveAllData = 0x0047FCE0;

			// SQLRETURN cfl_rs::exec_sql_direct(char const* sql, unsigned short timeout /* = 5 */)
			const unsigned int cfl_rs__exec_sql_direct = 0x00538300;

			// inline char const* const cfl_rs::_get_table() const
			const unsigned int cfl_rs___get_table = 0x0047DC70;
		}

		// GameServer.exe 1.38
		namespace GAMESERVER_138
		{
			// void CFightAble::WriteAttr(WPACKET &pk, Short sSynType)
			const unsigned int CFightAble_WriteAttr = 0x00505F00;

			// void	CFightAble::WriteAttr(WPACKET &pk, dbc::Short sStartAttr, dbc::Short sEndAttr, dbc::Short sSynType)
			const unsigned int CFightAble__WriteAttrEx = 0x00506090;

			// void CFightAble::WriteMonsAttr(WPACKET &pk, Short sSynType)
			const unsigned int CFightAble_WriteMonsAttr = 0x00505FB0;

			// void CFightAble::SynAttr(Short sType)
			const unsigned int CFightAble_SynAttr = 0x00504E70;

			// void CFightAble::SynAttrToSelf(Short sType)
			const unsigned int CFightAble_SynAttrToSelf = 0x00505050;

			// CParser
			const unsigned int CParser = 0x00610198;

			// int CParser::DoString(const char *csString, char chRetType, int nRetNum, ...)
			const unsigned int CParser__DoString = 0x00457E60;

			// int CParser::GetReturnNumber(char chID)
			const unsigned int CParser__GetReturnNumber = 0x00499C60;

			// bool WPacket::WriteLong(uLong lo)
			const unsigned int WPacket__WriteLong = 0x00524C40;

			// bool CTableCha::SaveAllData(CPlayer* pPlayer, char chSaveType)
			const unsigned int CTableCha__SaveAllData = 0x00483AC0;

			// SQLRETURN cfl_rs::exec_sql_direct(char const* sql, unsigned short timeout /* = 5 */)
			const unsigned int cfl_rs__exec_sql_direct = 0x005453F0;

			// inline char const* const cfl_rs::_get_table() const
			const unsigned int cfl_rs___get_table = 0x004818E0;
		}
	}
}