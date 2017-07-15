#include "hooks.h"
#include "Globals.h"
#include "Accessors.h"

KeyEventFn oKeyEvent;

int __fastcall Game::IN_KeyEvent(IBaseClientDll* client, int edx, int eventcode, int keynum, const char* pszCurrentBinding)
{
	if (Options.Menu.Opened)
		return 0;

	return oKeyEvent(client, edx, eventcode, keynum, pszCurrentBinding);
}