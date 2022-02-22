#pragma once

namespace pkodev
{
	namespace hook
	{
		// void CFightAble::WriteAttr(WPACKET & pk, Short sSynType)
		void __fastcall CFightAble__WriteAttr(void* This, void* NotUsed, void* pk, short int sSynType);

		// void	CFightAble::WriteAttr(WPACKET &pk, dbc::Short sStartAttr, dbc::Short sEndAttr, dbc::Short sSynType)
		void __fastcall CFightAble__WriteAttrEx(void* This, void* NotUsed, void* pk, short int sStartAttr, short int sEndAttr, short int sSynType);

		// void CFightAble::WriteMonsAttr(WPACKET &pk, Short sSynType)
		void __fastcall CFightAble__WriteMonsAttr(void* This, void* NotUsed, void* pk, short int sSynType);

		// void CFightAble::SynAttrToSelf(Short sType)
		void __fastcall CFightAble__SynAttrToSelf(void* This, void* NotUsed, short int sSynType);
	
		// bool CTableCha::SaveAllData(CPlayer* pPlayer, char chSaveType)
		bool __fastcall CTableCha__SaveAllData(void* This, void* NotUsed, void* pPlayer, char chSaveType);
	}
}