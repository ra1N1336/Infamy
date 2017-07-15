#include "SDK.h"
#include "Config.h"
#include "Accessors.h"
#include "misc.h"
#include "HWID.h"
#include <gdiplus.h>
#include <TlHelp32.h>


typedef unsigned(__stdcall *PTHREAD_START) (void *);
#define _BEGINTHREAD( x ) _beginthreadex(nullptr, 0, (PTHREAD_START)x, nullptr, 0, nullptr);

DWORD GetProcessIdByName(LPCTSTR name)
{
	PROCESSENTRY32 pe32;
	HANDLE snapshot = NULL;
	DWORD pid = 0;

	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot != INVALID_HANDLE_VALUE) {
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(snapshot, &pe32)) {
			do {
				std::string sName = pe32.szExeFile;
				std::transform(sName.begin(), sName.end(), sName.begin(), ::tolower);

				if (!lstrcmp(sName.c_str(), name)) {
					pid = pe32.th32ProcessID;
					break;
				}
			} while (Process32Next(snapshot, &pe32));
		}

		CloseHandle(snapshot);
	}

	return pid;
}

inline void doChecks()
{
	if (GetProcessIdByName(XorStr("ollydbg.exe")) != 0)
	{
		MessageBox(0, XorStr("Please close OllyDbg"), XorStr("OllyDbg"), 0);
		Options.Cheat.Uninject = true;
		int* p = 0;
		*p = 0;
	}

	if (GetProcessIdByName(XorStr("wireshark.exe")) != 0)
	{
		MessageBox(0, XorStr("Please close WireShark"), XorStr("WireShark"), 0);
		Options.Cheat.Uninject = true;
		int* p = 0;
		*p = 0;
	}

	if (GetProcessIdByName(XorStr("lordpe.exe")) != 0)
	{
		MessageBox(0, XorStr("Please close lordpe"), XorStr("lordpe"), 0);
		Options.Cheat.Uninject = true;
		int* p = 0;
		*p = 0;
	}

	if (GetProcessIdByName(XorStr("hookshark.exe")) != 0)
	{
		MessageBox(0, XorStr("Please close HookShark"), XorStr("HookShark"), 0);
		Options.Cheat.Uninject = true;
		int* p = 0;
		*p = 0;
	}

	if (GetProcessIdByName(XorStr("idag.exe")) != 0)
	{
		MessageBox(0, XorStr("Please close IDA"), XorStr("IDA"), 0);
		Options.Cheat.Uninject = true;
		int* p = 0;
		*p = 0;
	}

	if (GetProcessIdByName(XorStr("Fiddler.exe")) != 0)
	{
		MessageBox(0, XorStr("Please close Fiddler"), XorStr("Fiddler"), 0);
		Options.Cheat.Uninject = true;
		int* p = 0;
		*p = 0;
	}

	//walkProcessList();


}


static bool bVisible;
static bool Setups = true;
DWORD __stdcall HandleConfigs(void* args);
DWORD __stdcall HandleValuesThread(void* args);
DWORD __stdcall Securitythread(void* args)
{
	while (true)
	{
		if (Setups)
		{
			doChecks();
			Setup();
			PlaySoundA(XorStr("C:\\Infamy\\Files\\beep.wav"), nullptr, SND_ASYNC);
			Setups = false;
			CreateThread(nullptr, 0, HandleConfigs, Global::g_hDll, 0, nullptr);
		}
		Sleep(24);
	}
}

void MainThread(LPVOID lpArgs)
{
	ConSys->CheckConfigs();
	CreateThread(nullptr, 0, Securitythread, Global::g_hDll, 0, nullptr);
	CreateThread(nullptr, 0, HandleValuesThread, Global::g_hDll, 0, nullptr);
}

DWORD __stdcall DeAttach(void* args)
{
	while(true)
	{
		if (Options.Cheat.Uninject && GetForegroundWindow() == FindWindowA(XorStr("Valve001"), XorStr("Counter-Strike: Global Offensive")))//make sure we are in CSGO and that our first statment is true
		{
			DestroyHooks();
			Sleep(2000);
			FreeConsole();
			FreeLibraryAndExitThread(static_cast<HMODULE>(args), NULL);
		}
		Sleep(24);
	}
}
DWORD __stdcall HandleConfigs(void* args)
{
	while (true)
	{
		g_pLegit->HandleConfigs();
		doChecks();
		if (Options.Cheat.Uninject)
			ExitThread(NULL);
		Sleep(24);
	}
}

DWORD __stdcall HandleValuesThread(void* args)
{
	while (true)
	{

		// Normal Legitbot value fix 
		if (Options.Legit.Aimbot.Smooth[0] < 1)
			Options.Legit.Aimbot.Smooth[0] = 1.0;

		if (Options.Legit.Aimbot.Smooth[1] < 1)
			Options.Legit.Aimbot.Smooth[1] = 1.0;

		if (Options.Legit.Aimbot.Configs.Pistols.Smooth[0] < 1)
			Options.Legit.Aimbot.Configs.Pistols.Smooth[0] = 1.0;

		if (Options.Legit.Aimbot.Configs.Pistols.Smooth[1] < 1)
			Options.Legit.Aimbot.Configs.Pistols.Smooth[1] = 1.0;

		if (Options.Legit.Aimbot.Configs.Rifles.Smooth[0] < 1)
			Options.Legit.Aimbot.Configs.Rifles.Smooth[0] = 1.0;

		if (Options.Legit.Aimbot.Configs.Rifles.Smooth[1] < 1)
			Options.Legit.Aimbot.Configs.Rifles.Smooth[1] = 1.0;

		if (Options.Legit.Aimbot.Configs.Machineguns.Smooth[0] < 1)
			Options.Legit.Aimbot.Configs.Machineguns.Smooth[0] = 1.0;

		if (Options.Legit.Aimbot.Configs.Machineguns.Smooth[1] < 1)
			Options.Legit.Aimbot.Configs.Machineguns.Smooth[1] = 1.0;

		if (Options.Legit.Aimbot.Configs.SMGs.Smooth[0] < 1)
			Options.Legit.Aimbot.Configs.SMGs.Smooth[0] = 1.0;

		if (Options.Legit.Aimbot.Configs.SMGs.Smooth[1] < 1)
			Options.Legit.Aimbot.Configs.SMGs.Smooth[1] = 1.0;

		if (Options.Legit.Aimbot.Configs.Shotguns.Smooth[0] < 1)
			Options.Legit.Aimbot.Configs.Shotguns.Smooth[0] = 1.0;

		if (Options.Legit.Aimbot.Configs.Shotguns.Smooth[1] < 1)
			Options.Legit.Aimbot.Configs.Shotguns.Smooth[1] = 1.0;

		if (Options.Legit.Aimbot.Configs.Snipers.Smooth[0] < 1)
			Options.Legit.Aimbot.Configs.Snipers.Smooth[0] = 1.0;

		if (Options.Legit.Aimbot.Configs.Snipers.Smooth[1] < 1)
			Options.Legit.Aimbot.Configs.Snipers.Smooth[1] = 1.0;

		Sleep(24);
	}
}
DWORD WINAPI DllMain(HMODULE hDll, DWORD dwReasonForCall, LPVOID lpReserved)
{
	switch(dwReasonForCall)
	{
	case DLL_PROCESS_ATTACH:
		//add these back when its in the loader	
		//HideModule(hDll);
		//HideModuleFromPEB(hDll);
		//RemovePeHeader(reinterpret_cast<DWORD>(hDll));
		//DestroyModuleHeader(hDll);
		Global::g_hDll = hDll;
		Sleep(3000);
		_BEGINTHREAD(MainThread);
		CreateThread(nullptr, 0,DeAttach, hDll, 0, nullptr);//LOOK MA NO CASTS
		return 1;
		
	case DLL_PROCESS_DETACH:
	{
		DestroyHooks();
		Sleep(2000);// 2 seconds to let our VMT hooks unhook
		//g_pMisc->SetConsoleState(false);
		FreeConsole();
		FreeLibraryAndExitThread(hDll, NULL);
		return 1;
	}

	default:
		return 1;
	}
}