#include "Globals.h"
namespace Global
{
	CBaseEntity* LocalPlayer;
	HMODULE	g_hDll; 
	CUserCmd* pCmd;
	CUserCmd* oCmd;
	bool bSendPacket;
	bool isBombPlanted = false;
	bool IsPlayerDefusing = false;
	QAngle VisualAngle;
	WNDPROC oWndProc;
	bool Init;
	HWND Window;
	float oAAA[2];
	float  flHurtTime;
	int DamageDealt;
	float CurrTime;
	int DeathByHeadshot;
	int CurrentKey;
	std::vector<FloatingText> DamageHit;
	std::vector<ButtonCode_t> pressedKeys;
	int pressedkey;
	std::string* GlobalTextboxString;


	// PlayerList stuff
	int CurrentPlayer;
	char* CurrentPlayerName;
	bool PlayerSelected;

}
namespace Hooks
{
	VTHookManager* 	pClientMode;
	VTHookManager* 	pMovePacket;
	VTHookManager*  pPanel;
	VTHookManager*  pModel;
	VTHookManager*  pD3D;
	VTHookManager*  pTrace;
	VTHookManager*	pGEM;
	VTHookManager*  pEngine;
	VTHookManager*  MatSurface;
	VTHookManager*  RenderView;
}