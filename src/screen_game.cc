#include "entity.h"
#include "inputbox.h"
#include "screens.h"
#include <raylib.h>

void GameScreen::Init()
{
	framecounter = 0;
	constexpr Rectangle rect{ 5, 448 - 32 - 5, 512 - 10, 32 };
	this->inputbox = new InputBox{ rect };
	this->enemyPool = new EnemyPool{};

	this->enemyPool->Spawn("bonjour");
	TraceLog(LOG_INFO, "Game screen initialized");
}

void GameScreen::Update()
{
	++framecounter;
	this->enemyPool->UpdateAll();
	this->inputbox->Update();
}

void GameScreen::Draw()
{
	this->enemyPool->DrawAll();
	this->inputbox->Draw(framecounter);
}

void GameScreen::Unload()
{
	delete enemyPool;
	delete inputbox;
	TraceLog(LOG_INFO, "Game screen unloaded");
}