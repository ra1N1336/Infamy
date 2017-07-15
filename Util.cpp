#include "sdk.h"
#include "Globals.h"
#include "Hooks.h"
ServerRankRevealAllFn ServerRankRevealAllEx;
InitKeyValuesFn InitKeyValuesEx;
LoadFromBufferFn LoadFromBufferEx;
IsReadyFn IsReady;

void SetupInterfaces()
{
	Client = reinterpret_cast<IBaseClientDll*>(CaptureInterface(XorStr("client.dll"), XorStr("VClient")));
	printf("0x%X\n", reinterpret_cast<DWORD>(Client));
	if (!ClientMode) {
		auto uAddress = *(DWORD*)(Memory::FindPatternIDA(XorStr("client.dll"), XorStr("8B 35 ? ? ? ? 85 FF 74 73")) + 2);
		ClientMode = *reinterpret_cast<IClientModeShared**>(uAddress);
	}
	printf("0x%X\n", reinterpret_cast<DWORD>(ClientMode));
	ClientEntList = reinterpret_cast<IClientEntityList*>(CaptureInterface(XorStr("client.dll"), XorStr("VClientEntityList")));
	printf("0x%X\n", reinterpret_cast<DWORD>(ClientEntList));
	Cvar = reinterpret_cast<ICVar*>(CaptureInterface(XorStr("vstdlib.dll"), XorStr("VEngineCvar")));
	printf("0x%X\n", reinterpret_cast<DWORD>(Cvar));
	Engine = reinterpret_cast<IEngineClient*>(CaptureInterface(XorStr("engine.dll"), XorStr("VEngineClient")));
	printf("0x%X\n", reinterpret_cast<DWORD>(Engine));
	EngineTrace = reinterpret_cast<IEngineTrace*>(CaptureInterface(XorStr("engine.dll"), XorStr("EngineTraceClient")));
	printf("0x%X\n", reinterpret_cast<DWORD>(EngineTrace));
	auto ClientVMT = *reinterpret_cast<DWORD**>(Client);
	printf("0x%X\n", reinterpret_cast<DWORD>(ClientVMT));
	g_pCInput = *reinterpret_cast<CInput**>(ClientVMT[15] + 0x1);
	printf("0x%X\n", reinterpret_cast<DWORD>(g_pCInput));
	Globals = **reinterpret_cast<IGlobalVarsBase***>((*reinterpret_cast<DWORD**>(Client))[0] + 0x53);
	printf("0x%X\n", reinterpret_cast<DWORD>(Globals));
	Surface = reinterpret_cast<ISurface*>(CaptureInterface(XorStr("vguimatsurface.dll"), XorStr("VGUI_Surface")));
	printf("0x%X\n", reinterpret_cast<DWORD>(Surface));
	VPanel = reinterpret_cast<IVPanel*>(CaptureInterface(XorStr("vgui2.dll"), XorStr("VGUI_Panel")));
	printf("0x%X\n",reinterpret_cast<DWORD>(VPanel));
	RenderView = reinterpret_cast<IVRenderView*>(CaptureInterface(XorStr("engine.dll"), XorStr("VEngineRenderView")));
	printf("0x%X\n", reinterpret_cast<DWORD>(RenderView));
	ModelRender = reinterpret_cast<IVModelRender*>(CaptureInterface(XorStr("engine.dll"), XorStr("VEngineModel")));
	printf("0x%X\n", reinterpret_cast<DWORD>(ModelRender));
	MaterialSystem = reinterpret_cast<IMaterialSystem*>(CaptureInterface(XorStr("materialsystem.dll"), XorStr("VMaterialSystem")));
	printf("0x%X\n", reinterpret_cast<DWORD>(MaterialSystem));
	ModelInfo = reinterpret_cast<IVModelInfo*>(CaptureInterface(XorStr("engine.dll"), XorStr("VModelInfoClient")));
	printf("0x%X\n", reinterpret_cast<DWORD>(ModelInfo));
	Prediction = reinterpret_cast<IPrediction*>(CaptureInterface(XorStr("client.dll"), XorStr("VClientPrediction")));
	printf("0x%X\n", reinterpret_cast<DWORD>(Prediction));
	g_pMovement = reinterpret_cast<CGameMovement*>(CaptureInterface(XorStr("client.dll"), XorStr("GameMovement")));
	Physprops = reinterpret_cast<IPhysicsSurfaceProps*>(CaptureInterface(XorStr("vphysics.dll"), XorStr("VPhysicsSurfaceProps")));
	printf("0x%X\n", reinterpret_cast<DWORD>(Physprops));
	DebugOverlay = reinterpret_cast<IVDebugOverlay*>(CaptureInterface(XorStr("engine.dll"), XorStr("VDebugOverlay")));
	printf("0x%X\n", reinterpret_cast<DWORD>(DebugOverlay));
	StudioRender = reinterpret_cast<IStudioRender*>(CaptureInterface(XorStr("studiorender.dll"), XorStr("VStudioRender")));
	printf("0x%X\n", reinterpret_cast<DWORD>(StudioRender));
	GameEventManager = reinterpret_cast<IGameEventManager2*>(CaptureInterface(XorStr("engine.dll"), XorStr("GAMEEVENTSMANAGER")));
	printf("0x%X\n", reinterpret_cast<DWORD>(GameEventManager));
	InputSystem = reinterpret_cast<IInputSystem*>(CaptureInterface(XorStr("inputsystem.dll"), XorStr("InputSystemVersion")));
	printf("0x%X\n", reinterpret_cast<DWORD>(InputSystem));
	g_pEffects = reinterpret_cast<IVEffects*>(CaptureInterface(XorStr("engine.dll"), XorStr("VEngineEffects")));
	printf("0x%X\n", reinterpret_cast<DWORD>(g_pEffects));
	g_pMoveHelper = **reinterpret_cast<CMoveHelper***>(Memory::FindPatternAlt("client.dll", reinterpret_cast<PBYTE>("\x8B\x0D\x00\x00\x00\x00\x6A\x02\x8B\x01\xFF\x50\x28"), "xx????xxxxxxx", 0, 0) + 0x2);
	//Global::Window = FindWindowA(XorStr("Valve001"), XorStr("Counter-Strike: Global Offensive")); Sleep(200);
	//Global::oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(Global::Window, GWL_WNDPROC, reinterpret_cast<LONG_PTR>(Game::hkdWndProc)));
}



CBaseEntity* GetLocalPlayer()
{
	return ClientEntList->GetClientEntity(Engine->GetLocalPlayer());
}

CNetVarManager* NetVars = new CNetVarManager;


wchar_t* ConvertCharArrayToLPCWSTR(const char* charArray)
{
	auto wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

void TraceLine(const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, CBaseEntity* ignore, trace_t* ptr)
{
	Ray_t ray;
	ray.Init(vecAbsStart, vecAbsEnd);
	CTraceFilter filter;
	filter.pSkip = ignore;

	EngineTrace->TraceRay(ray, mask, &filter, ptr);
}


void UTIL_TraceLine(Vector& vecAbsStart, Vector& vecAbsEnd, unsigned int mask, const IHandleEntity *ignore, int collisionGroup, trace_t *ptr)
{

	Ray_t ray;
	ray.Init(vecAbsStart, vecAbsEnd);
	CTraceFilter traceFilter;
	traceFilter.pSkip = (void*)ignore;
	EngineTrace->TraceRay(ray, mask, &traceFilter, ptr);

}

void UTIL_ClipTraceToPlayers(Vector& vecAbsStart, Vector& vecAbsEnd, unsigned int mask, ITraceFilter* filter, trace_t* tr)
{
	trace_t playerTrace;
	Ray_t ray;
	float smallestFraction = tr->fraction;
	const float maxRange = 60.0f;

	ray.Init(vecAbsStart, vecAbsEnd);

	for (int k = 1; k <= Globals->maxClients; ++k)
	{
		CBaseEntity *player = ClientEntList->GetClientEntity(k);

		if (!player || !player->GetAlive())
			continue;

		if (player->GetDormant())
			continue;


		if (filter && filter->ShouldHitEntity(player, mask) == false)
			continue;

		float range = DistanceToRay(player->WorldSpaceCenter(), vecAbsStart, vecAbsEnd);
		if (range < 0.0f || range > maxRange)
			continue;

		EngineTrace->ClipRayToEntity(ray, mask | CONTENTS_HITBOX, (IHandleEntity*)player, &playerTrace);
		if (playerTrace.fraction < smallestFraction)
		{
			// we shortened the ray - save off the trace
			*tr = playerTrace;
			smallestFraction = playerTrace.fraction;
		}
	}

}

float DistanceToRay(const Vector &pos, const Vector &rayStart, const Vector &rayEnd, float *along, Vector *pointOnRay)
{
	Vector to = pos - rayStart;
	Vector dir = rayEnd - rayStart;
	float length = dir.NormalizeInPlace();

	float rangeAlong = DotProduct(dir, to);
	if (along)
	{
		*along = rangeAlong;
	}

	float range;

	if (rangeAlong < 0.0f)
	{
		// off start point
		range = -(pos - rayStart).Length();

		if (pointOnRay)
		{
			*pointOnRay = rayStart;
		}
	}
	else if (rangeAlong > length)
	{
		// off end point
		range = -(pos - rayEnd).Length();

		if (pointOnRay)
		{
			*pointOnRay = rayEnd;
		}
	}
	else // within ray bounds
	{
		Vector onRay = rayStart + (dir.operator*(rangeAlong));
		range = (pos - onRay).Length();

		if (pointOnRay)
		{
			*pointOnRay = onRay;
		}
	}

	return range;
}


void InitKeyValues(KeyValues* pKeyValues, const char* name)
{
	InitKeyValuesEx = reinterpret_cast<InitKeyValuesFn>(offsets.InitKeyValuesEx);
	InitKeyValuesEx(pKeyValues, name);
}

void LoadFromBuffer(KeyValues* pKeyValues, const char* resourceName, const char* pBuffer, void* pFileSystem, const char* pPathID, void* pfnEvaluateSymbolProc)
{
	LoadFromBufferEx = reinterpret_cast<LoadFromBufferFn>(offsets.LoadFromBufferEx);
	LoadFromBufferEx(pKeyValues, resourceName, pBuffer, pFileSystem, pPathID, pfnEvaluateSymbolProc);
}

void SendPacket(byte toggle)
{
	*reinterpret_cast<byte*>(offsets.SendPacket) = toggle;
}

void SetupHooks()
{
	Hooks::pClientMode = new VTHookManager(reinterpret_cast<DWORD**>(ClientMode));
	Hooks::pMovePacket = new VTHookManager(reinterpret_cast<DWORD**>(Client));
	Hooks::pPanel = new VTHookManager(reinterpret_cast<PDWORD*>(VPanel));
	Hooks::pModel = new VTHookManager(reinterpret_cast<DWORD**>(ModelRender));
	//Hooks::pD3D = new VTHookManager(reinterpret_cast<DWORD**>(offsets.d3d9Device));
	Hooks::pTrace = new VTHookManager(reinterpret_cast<DWORD**>(EngineTrace));
	Hooks::pGEM = new VTHookManager(reinterpret_cast<DWORD**>(GameEventManager));
	Hooks::pEngine = new VTHookManager(reinterpret_cast<DWORD**>(Engine));
	Hooks::MatSurface = new VTHookManager(reinterpret_cast<DWORD**>(Surface));


	//Hook
	oOverrideView = reinterpret_cast<OverrideViewFn>(Hooks::pClientMode->dwHookMethod(reinterpret_cast<DWORD>(Game::HookedOverrideView), 18));
	oPaintTraverse = reinterpret_cast<PaintTraverseFn>(Hooks::pPanel->dwHookMethod(reinterpret_cast<DWORD>(Game::hkdPaintTraverse), 41));
	oCreateMove = reinterpret_cast<CreateMoveFn>(Hooks::pMovePacket->dwHookMethod(reinterpret_cast<DWORD>(Game::hkdCreateMove), 21));// Client Mode because easier as of right now
	oDrawModelExecute = reinterpret_cast<DrawModelExecuteFn>(Hooks::pModel->dwHookMethod(reinterpret_cast<DWORD>(Game::DrawModelExecute), 21));
	//oResetScene = reinterpret_cast<tReset>(Hooks::pD3D->dwHookMethod(reinterpret_cast<DWORD>(Game::hkdReset), 16));
	//oEndScene = reinterpret_cast<tEndScene>(Hooks::pD3D->dwHookMethod(reinterpret_cast<DWORD>(Game::hkdEndScene), 42));
	//oTraceRay = reinterpret_cast<TraceRayFn>(Hooks::pTrace->dwHookMethod(reinterpret_cast<DWORD>(Game::TraceRayhk), 5));
	oFrameStageNotify = reinterpret_cast<FrameStageNotifyFn>(Hooks::pMovePacket->dwHookMethod(reinterpret_cast<DWORD>(Game::hkdFrameStageNotify), 36));
	oFireEventClientSide = reinterpret_cast<FireEventClientSideFn>(Hooks::pGEM->dwHookMethod(reinterpret_cast<DWORD>(Game::FireEventClientSideThink), 9));
	oPlaySound = reinterpret_cast<PlaySoundFn>(Hooks::MatSurface->dwHookMethod(reinterpret_cast<DWORD>(Game::Hooked_PlaySound), 82));
	oClientCmdUnrestricted = reinterpret_cast<ClientCmdFn>(Hooks::pEngine->dwHookMethod(reinterpret_cast<DWORD>(Game::Hooked_ClientCmdUnrestricted), 114));
	//Hooks::pMovePacket->dwHookMethod(reinterpret_cast<DWORD>(Game::IN_KeyEvent), 20);
	//oKeyEvent = reinterpret_cast<KeyEventFn>(Hooks::pMovePacket->dwHookMethod(reinterpret_cast<DWORD>(Game::IN_KeyEvent), 20));

}
void DestroyHooks()
{
	SetWindowLongPtr(Global::Window, GWL_WNDPROC, reinterpret_cast<LONG_PTR>(Global::oWndProc));
	Hooks::pClientMode->UnHook();
	Hooks::pClientMode->dwUnHookMethod(18);
	Hooks::pMovePacket->UnHook();
	Hooks::pMovePacket->dwUnHookMethod(36);
	Hooks::pMovePacket->dwUnHookMethod(21);
	//Hooks::pMovePacket->dwUnHookMethod(20);
	Hooks::pPanel->UnHook();
	Hooks::pPanel->dwUnHookMethod(41);
	Hooks::pModel->UnHook();	
	Hooks::pModel->dwUnHookMethod(21);
	//Hooks::pD3D->UnHook();
	//Hooks::pD3D->dwUnHookMethod(16);
	//Hooks::pD3D->dwUnHookMethod(42);
	Hooks::pGEM->UnHook();
	Hooks::pGEM->dwUnHookMethod(9);
	Hooks::MatSurface->UnHook();
	Hooks::MatSurface->dwUnHookMethod(82);
	Hooks::pEngine->UnHook();
	Hooks::pEngine->dwUnHookMethod(114);
	//ImGui_ImplDX9_Shutdown();
	//Global::g_pRenderer->OnLostDevice();
	//Infamy->Release();
}
void SetupOffsets()
{
	NetVars->Initialize();
	GrabOffsets();
}

void SetupTextures()
{
	visible_flat = MaterialSystem->CreateMaterial(true, false, false);
	visible_tex = MaterialSystem->CreateMaterial(false, false, false);
	hidden_flat = MaterialSystem->CreateMaterial(true, true, false);
	hidden_tex = MaterialSystem->CreateMaterial(false, true, false);
}

void Setup()
{
	SetupInterfaces();

	SetupOffsets();

	SetupFonts();

	SetupTextures();

	SetupHooks();

	
}

char GetButtonString(ButtonCode_t key)
{

	switch (key)
	{
	case KEY_PAD_0:
		return '0';
	case KEY_PAD_1:
		return '1';
	case KEY_PAD_2:
		return '2';
	case KEY_PAD_3:
		return '3';
	case KEY_PAD_4:
		return '4';
	case KEY_PAD_5:
		return '5';
	case KEY_PAD_6:
		return '6';
	case KEY_PAD_7:
		return '7';
	case KEY_PAD_8:
		return '8';
	case KEY_PAD_9:
		return '9';
	case KEY_PAD_DIVIDE:
		return '/';
	case KEY_PAD_MULTIPLY:
		return '*';
	case KEY_PAD_MINUS:
		return '-';
	case KEY_PAD_PLUS:
		return '+';
	case KEY_SEMICOLON:
		return ';';
	default:
		return InputSystem->ButtonCodeToString(key)[0];
	}
}

char GetUpperValueOf(ButtonCode_t key)
{


	switch (key)
	{
	case KEY_0:
		return ')';
	case KEY_1:
		return '!';
	case KEY_2:
		return '@';
	case KEY_3:
		return '#';
	case KEY_4:
		return '$';
	case KEY_5:
		return '%';
	case KEY_6:
		return '^';
	case KEY_7:
		return '&';
	case KEY_8:
		return '*';
	case KEY_9:
		return '(';
	case KEY_LBRACKET:
		return '{';
	case KEY_RBRACKET:
		return '}';
	case KEY_SEMICOLON:
		return ':';
	case KEY_APOSTROPHE:
		return '"';
	case KEY_BACKQUOTE:
		return '~';
	case KEY_COMMA:
		return '<';
	case KEY_PERIOD:
		return '>';
	case KEY_SLASH:
		return '?';
	case KEY_BACKSLASH:
		return '|';
	case KEY_MINUS:
		return '_';
	case KEY_EQUAL:
		return '+';
	default:
		char buttonChar = GetButtonString(key);

		if (buttonChar >= 'a' && buttonChar <= 'z')
			buttonChar -= 32;

		return buttonChar;
	}
}