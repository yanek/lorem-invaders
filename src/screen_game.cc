#include "entity.h"
#include "inputbox.h"
#include "screens.h"
#include <raylib.h>

static int framecounter{0};
static InputBox* inputbox{nullptr};
static EnemyPool* enemyPool{nullptr};

void InitGameScreen()
{
	framecounter = 0;
	constexpr Rectangle rect{ 5, 448 - 32 - 5, 512 - 10, 32 };
	inputbox = new InputBox{ rect };
	enemyPool = new EnemyPool{};

	enemyPool->Spawn("bonjour");
	TraceLog(LOG_INFO, "Game screen initialized");
}

void UpdateGameScreen()
{
	++framecounter;
	enemyPool->UpdateAll();
	inputbox->Update();
}

void DrawGameScreen()
{
	enemyPool->DrawAll();
	inputbox->Draw(framecounter);
}

void UnloadGameScreen()
{
	free(enemyPool);
	free(inputbox);
	TraceLog(LOG_INFO, "Game screen unloaded");
}