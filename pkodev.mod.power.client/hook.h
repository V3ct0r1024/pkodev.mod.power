#pragma once
#include "structure.h"

namespace pkodev
{
	namespace hook
	{
		// void ReadChaAttrPacket(LPRPACKET pk, stNetChaAttr &SChaAttr, char* szLogName)
		void __cdecl ReadChaAttrPacket(void* pk, void* SChaAttr, char* szLogName);
		
		// void NetActorDestroy(unsigned int nID, char chSeeType)
		void __cdecl NetActorDestroy(unsigned int nID, char chSeeType);

		// void CHeadSay::Render(D3DXVECTOR3& pos)
		void __fastcall CHeadSay__Render(void* This, void* NotUsed, D3DXVECTOR3& Pos);
	}
}