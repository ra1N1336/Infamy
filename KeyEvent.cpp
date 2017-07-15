#include "hooks.h"
#include "Globals.h"
#include <unordered_map>
#include "Accessors.h"
#include "Framework.h"
KeyEventFn oKeyEvent;
bool bPressedKey, bKeyDown;

/*int __stdcall Game::IN_KeyEvent(int eventcode, int keynum, const char* pszCurrentBinding)
{

		if (Options.Menu.PlayerMods)
		{

				if (InputSystem->IsButtonDown((ButtonCode_t)keynum) && Input->hwCSGO == GetActiveWindow())
				{
					bPressedKey = false;
					bKeyDown = true;
				}
				else if (!InputSystem->IsButtonDown((ButtonCode_t)keynum) && bKeyDown)
				{
					bPressedKey = true;
					bKeyDown = false;
				}
				else
				{
					bPressedKey = false;
					bKeyDown = false;
				}

				if (bPressedKey)
				{
					cTextBox->HandleKeys(keynum);
				}
				return 0;
		}

	return oKeyEvent(eventcode, keynum, pszCurrentBinding);
}*/
