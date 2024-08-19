#include <raylib.h>
#include "screens.h"

GameScreen currentScreen = SCR_TITLE;
Font res_font16 = { 0 };

void ChangeToScreen(const int newScreen)
{
	switch (currentScreen)
	{
	case SCR_TITLE:
		UnloadTitleScreen();
		break;
	case SCR_GAME:
		UnloadGameScreen();
		break;
	default:
		TraceLog(LOG_ERROR, "Cannot unload unknown screen");
		break;
	}

	currentScreen = newScreen;

	switch (currentScreen)
	{
	case SCR_TITLE:
		InitTitleScreen();
		break;
	case SCR_GAME:
		InitGameScreen();
		break;
	default:
		TraceLog(LOG_ERROR, "Cannot load unknown screen");
		break;
	}
}