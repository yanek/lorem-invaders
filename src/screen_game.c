#include "inputbox.h"
#include "screens.h"
#include <raylib.h>

int frameCounter = 0;
InputBox inputbox = { 0 };

void InitGameScreen(void)
{
	frameCounter = 0;
	inputbox = InitInputBox((Rectangle){ 5, 448 - 32 - 5, 512 - 10, 32 }, &font);
	TraceLog(LOG_INFO, "Game screen initialized");
}

void UpdateGameScreen(void)
{
	frameCounter++;
	UpdateInputBox(&inputbox);
}

void DrawGameScreen(void)
{
	DrawInputBox(&inputbox, frameCounter);
}

void UnloadGameScreen(void)
{
	TraceLog(LOG_INFO, "Game screen unloaded");
}