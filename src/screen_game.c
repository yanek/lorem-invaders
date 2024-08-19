#include "entity.h"
#include "inputbox.h"
#include "screens.h"
#include <raylib.h>

static int _framecounter = 0;
static InputBox _inputbox = { 0 };

void InitGameScreen(void)
{
	_framecounter = 0;
	_inputbox = InitInputBox((Rectangle){ 5, 448 - 32 - 5, 512 - 10, 32 }, &font);
	InitEnemies();

	CreateEnemy("Bonjour");
	TraceLog(LOG_INFO, "Game screen initialized");
}

void UpdateGameScreen(void)
{
	++_framecounter;
	UpdateEnemies();
	UpdateInputBox(&_inputbox);
}

void DrawGameScreen(void)
{
	DrawEnemies();
	DrawInputBox(&_inputbox, _framecounter);
}

void UnloadGameScreen(void)
{
	TraceLog(LOG_INFO, "Game screen unloaded");
}