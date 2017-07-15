#include "Hooks.h"
#include "Globals.h"
#include "Accessors.h"
OnScreenSizeChanged_t oOnScreenSizeChange;
void __stdcall Game::OnScreenSizeChanged(int nOldWidth, int nOldHeight)
{
	oOnScreenSizeChange(Surface, nOldWidth, nOldHeight);

	initializeFonts();
}





