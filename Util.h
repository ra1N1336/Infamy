#pragma once

#define RandomInt(min, max) (rand() % (max - min + 1) + min)

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

#define MakePtr (cast, ptr, addValue) ( cast )( (DWORD)( ptr ) + ( DWORD )( addValue ) )
#include "Sprite.h"
class KeyValues;

using MsgFn = void(__cdecl*)(char const *, ...);
using ServerRankRevealAllFn = bool(__cdecl*)(float*);
using InitKeyValuesFn = void(__thiscall*)(void* thisptr, const char* name);
using LoadFromBufferFn = void(__thiscall*)(void* thisptr, const char* resourceName, const char* pBuffer, void* pFileSystem, const char* pPathID, void* pfnEvaluateSymbolProc);
using IsReadyFn = void(__cdecl*)();

	extern MsgFn PrintMessage;
	extern ServerRankRevealAllFn ServerRankRevealAllEx;
	extern InitKeyValuesFn InitKeyValuesEx;
	extern LoadFromBufferFn LoadFromBufferEx;
	extern IsReadyFn IsReady;

	extern CBaseEntity* GetLocalPlayer();
	extern CNetVarManager* NetVars;
	extern void SpoofCvar(ConVar* pCvar);
	extern wchar_t* ConvertCharArrayToLPCWSTR(const char* charArray);

	extern void InitKeyValues(KeyValues* pKeyValues, const char* name);
	extern void LoadFromBuffer(KeyValues* pKeyValues, const char* resourceName, const char* pBuffer, void* pFileSystem = nullptr, const char* pPathID = nullptr, void* pfnEvaluateSymbolProc = nullptr);
	extern void SendPacket(byte toggle);
	extern void SetupInterfaces();
	extern void SetupHooks();
	extern void SetupOffsets();
	extern void SetupTextures();
	extern void Setup();
	extern void DestroyHooks();
	extern char GetButtonString(ButtonCode_t key);
	extern char GetUpperValueOf(ButtonCode_t key);
	extern int random(int min, int max);
	extern float random(float min, float max);
	extern float DistanceToRay(const Vector &pos, const Vector &rayStart, const Vector &rayEnd, float *along = NULL, Vector *pointOnRay = NULL);
	extern void UTIL_ClipTraceToPlayers(Vector& vecAbsStart, Vector& vecAbsEnd, unsigned int mask, ITraceFilter* filter, trace_t* tr);
	extern void UTIL_TraceLine(Vector& vecAbsStart, Vector& vecAbsEnd, unsigned int mask, const IHandleEntity *ignore, int collisionGroup, trace_t *ptr);

	typedef void* (*CreateInterface_t)(const char*, int*);
	inline void* CaptureInterface(const char* chHandle, const char* chInterfaceName)
	{
		volatile auto handlegotten = (GetModuleHandleA(chHandle) != nullptr);
		while (!GetModuleHandleA(chHandle)) Sleep(100);
		void* fnFinal = nullptr;
		auto PossibleInterfaceName = new char[strlen(chInterfaceName) + 4];
		auto TestInterface = reinterpret_cast<CreateInterface_t>(GetProcAddress(GetModuleHandleA(chHandle), XorStr("CreateInterface")));
		for (auto i = 100; i > 0; i--)
		{
			XorCompileTime::w_sprintf(PossibleInterfaceName, XorStr("%s%03i"), chInterfaceName, i);
			fnFinal = static_cast<void*>(TestInterface(PossibleInterfaceName, nullptr));

			if (fnFinal != nullptr)
				break;
			
		}
		delete PossibleInterfaceName;
		return fnFinal;
	}

	
	

