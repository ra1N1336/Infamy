#pragma once
#include "sdk.h"
#include "Hooks.h"
#include "draw.h"
#include "Options.h"
#include "Sprite.h"
#include "Accessors.h"
#include <vector>

class FloatingText;



namespace Global
{
	extern CUserCmd* pCmd;
	extern CBaseEntity* LocalPlayer;	
	extern QAngle VisualAngle;
	extern bool bSendPacket;
	extern CUserCmd* oCmd;
	extern bool bAimStepDone;
	extern bool isBombPlanted;
	extern bool IsPlayerDefusing;
	extern QAngle AimStepAngle;
	extern float  flHurtTime;
	extern bool Init;
	extern WNDPROC oWndProc;
	extern HWND Window;
	extern float oAAA[2];
	extern HMODULE g_hDll;
	extern int DamageDealt;
	extern float CurrTime;
	extern int DeathByHeadshot;
	extern std::vector<FloatingText> DamageHit;
	extern int CurrentKey;
	extern std::vector<ButtonCode_t> pressedKeys;
	extern int pressedkey;
	extern std::string* GlobalTextboxString;

	// PlayerList stuff
	extern int CurrentPlayer;
	extern char* CurrentPlayerName;
	extern bool  PlayerSelected;

}
namespace Hooks
{
	extern VTHookManager* 	pClientMode;
	extern VTHookManager* 	pMovePacket;
	extern VTHookManager*   pPanel;
	extern VTHookManager*   pModel;
	extern VTHookManager*   pD3D;
	extern VTHookManager*   pTrace;
	extern VTHookManager*	pGEM;
	extern VTHookManager*   pEngine;
	extern VTHookManager*   MatSurface;
	extern VTHookManager*	RenderView;
}