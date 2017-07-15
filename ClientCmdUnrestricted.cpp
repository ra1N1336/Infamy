#include "hooks.h"
#include "Globals.h"
#include "Accessors.h"

ClientCmdFn oClientCmdUnrestricted;

void SetClanTags(const char* tag, const char* name)
{
	typedef void(__fastcall* pSetClanTagFn)(const char*, const char*);
	static auto pSetClanTag = reinterpret_cast<pSetClanTagFn>(Memory::FindPatternAlt(XorStr("engine.dll"),
		reinterpret_cast<PBYTE>(XorStr("\x53\x56\x57\x8B\xDA\x8B\xF9\xFF\x15\x00\x00\x00\x00\x6A\x24\x8B\xC8\x8B\x30")), XorStr("xxxxxxxxx????xxxxxx"), 0, 0));

	pSetClanTag(tag, name);
}

void __stdcall Game::Hooked_ClientCmdUnrestricted(const char *szCmdString, char flag) {
	std::string str(szCmdString);
	std::string prefix("thirdperson");
	std::string prefix2("update");
	if (!str.compare(0, prefix.size(), prefix)) {
		str.replace(0, prefix.size(), "");
		g_pPlayer->SpoofConvars();
		Engine->ExecuteClientCmd("thirdperson");
	}
	else if (!str.compare(0, prefix2.size(), prefix2)) {
		str.replace(0, prefix2.size(), "");
		ConVar *clfullupdate = Cvar->FindVar("cl_fullupdate");
		clfullupdate->nFlags = FCVAR_NONE;
		Engine->ClientCmd_Unrestricted("cl_fullupdate");
	}
	else
		oClientCmdUnrestricted(szCmdString, flag);
}
