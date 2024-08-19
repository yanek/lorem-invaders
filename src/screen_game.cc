#include "entity.h"
#include "inputbox.h"
#include "screens.h"
#include <raylib.h>

static int framecounter = 0;
static InputBox inputbox = { 0 };

void InitGameScreen()
{
	framecounter = 0;
	inputbox = InitInputBox(Rectangle{ 5, 448 - 32 - 5, 512 - 10, 32 });
	InitEnemies();

	CreateEnemy("bonjour");
	TraceLog(LOG_INFO, "Game screen initialized");
}

void UpdateGameScreen()
{
	++framecounter;
	UpdateEnemies();
	UpdateInputBox(&inputbox);
}

void DrawGameScreen()
{
	DrawEnemies();
	DrawInputBox(&inputbox, framecounter);
}

void UnloadGameScreen()
{
	TraceLog(LOG_INFO, "Game screen unloaded");
}