#pragma once
#include "address.h"
#include "structure.h"

namespace pkodev
{
	namespace pointer
	{
		// void ReadChaAttrPacket(LPRPACKET pk, stNetChaAttr &SChaAttr, char* szLogName)
		typedef void(__cdecl* ReadChaAttrPacket__Ptr)(void*, void*, char *);
		ReadChaAttrPacket__Ptr ReadChaAttrPacket = (ReadChaAttrPacket__Ptr)(void*)(address::MOD_EXE_VERSION::ReadChaAttrPacket);
	
		// uLong RPacket::ReadLong()
		typedef int(__thiscall* RPacket__ReadLong_Ptr)(void*);
		RPacket__ReadLong_Ptr RPacket__ReadLong = (RPacket__ReadLong_Ptr)(void*)(address::MOD_EXE_VERSION::RPacket__ReadLong);
		
		// void CHeadSay::Render(D3DXVECTOR3& pos)
		typedef void(__thiscall* CHeadSay__Render__Ptr)(void*, D3DXVECTOR3&);
		CHeadSay__Render__Ptr CHeadSay__Render = (CHeadSay__Render__Ptr)(void*)(address::MOD_EXE_VERSION::CHeadSay__Render);
	
		// void CGuiFont::BRender(unsigned int nIndex, const char* str, int x, int y, DWORD color, DWORD shadow)
		typedef void(__thiscall* CGuiFont_BRender_Ptr)(void*, const char*, int, int, int, int);
		CGuiFont_BRender_Ptr CGuiFont_BRender = (CGuiFont_BRender_Ptr)(void*)(address::MOD_EXE_VERSION::CGuiFont__BRender);

		// BOOL MPRender::WorldToScreen(float fX, float fY, float fZ, int *pnX, int *pnY)
		typedef bool(__thiscall* MPRender__WorldToScreen__Ptr)(void*, float, float, float, int*, int*);
		MPRender__WorldToScreen__Ptr MPRender__WorldToScreen = reinterpret_cast<MPRender__WorldToScreen__Ptr>(*reinterpret_cast<unsigned int *>(address::MOD_EXE_VERSION::MPRender__WorldToScreen));

		// SIZE* CMPFont::GetTextSize(char* szText, SIZE* pSize, float fScale = 1.0f);
		typedef tagSIZE* (__thiscall* CMPFont__GetTextSize__Ptr)(void*, char*, tagSIZE*, float);
		CMPFont__GetTextSize__Ptr CMPFont__GetTextSize = reinterpret_cast<CMPFont__GetTextSize__Ptr>(*reinterpret_cast<unsigned int*>(address::MOD_EXE_VERSION::CMPFont__GetTextSize));
		
		// bool CCharacter::GetIsFly()
		typedef bool(__thiscall* CCharacter__GetIsFly__Ptr)(void*);
		CCharacter__GetIsFly__Ptr CCharacter__GetIsFly = (CCharacter__GetIsFly__Ptr)(void*)(address::MOD_EXE_VERSION::CCharacter__GetIsFly);

		// void NetActorDestroy(unsigned int nID, char chSeeType)
		typedef void(__cdecl* NetActorDestroy__Ptr)(unsigned int, char);
		NetActorDestroy__Ptr NetActorDestroy = (NetActorDestroy__Ptr)(void*)(address::MOD_EXE_VERSION::NetActorDestroy);

		// CCharacter* CGameScene::SearchByID(unsigned long id)
		typedef void*(__thiscall* CGameScene__SearchByID__Ptr)(void*, unsigned int);
		CGameScene__SearchByID__Ptr CGameScene__SearchByID = (CGameScene__SearchByID__Ptr)(void*)(address::MOD_EXE_VERSION::CGameScene__SearchByID);
	}
}