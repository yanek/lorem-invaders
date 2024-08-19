#include <raylib.h>
#include "screens.h"

void InitGameScreen(void)
{
	TraceLog(LOG_INFO, "Game screen initialized");
}

void UpdateGameScreen(void)
{
	if (IsKeyPressed(KEY_ENTER))
	{
		ChangeToScreen(SCR_TITLE);
	}
}

void DrawGameScreen(void)
{
	DrawText("Lorem Invader", 10, 50, 40, RAYWHITE);
	DrawText("234", 10, 50, 60, RAYWHITE);
}

void UnloadGameScreen(void)
{
	TraceLog(LOG_INFO, "Game screen unloaded");
}