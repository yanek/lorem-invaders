#include <raylib.h>
#include "screens.h"

GameScreen currentScreen = SCR_TITLE;

void ChangeToScreen(const GameScreen newScreen)
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