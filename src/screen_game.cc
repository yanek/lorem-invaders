#include "entity.h"
#include "inputbox.h"
#include "screens.h"
#include "viewport.h"
#include <raylib.h>

GameScreen::GameScreen(const GameMode mode)
	: Screen("game_screen"), lipsum{ mode }
{
}

Player *GameScreen::GetPlayer() const
{
	return this->player;
}

EnemyPool *GameScreen::GetEnemyPool() const
{
	return this->enemyPool;
}

InputBox *GameScreen::GetInputBox() const
{
	return this->inputbox;
}

void GameScreen::Init()
{
	framecounter = 0;

	constexpr Rectangle rect{
		5,
		Viewport::gameHeight - 32 - 5,
		Viewport::gameWidth - 10,
		32
	};

	this->player = new Player{};
	this->inputbox = new InputBox{ rect };
	this->enemyPool = new EnemyPool{};
}

void GameScreen::Update()
{
	const float delta = GetFrameTime();
	++framecounter;
	this->enemyPool->UpdateAll(this, delta);
	this->inputbox->Update();

	if (framecounter % 120 == 0)
	{
		this->enemyPool->Spawn(lipsum.Next());
	}
}

void GameScreen::Draw()
{
	this->enemyPool->DrawAll();
	this->inputbox->Draw(framecounter);
	this->player->DrawHud();
}

void GameScreen::Unload()
{
	delete player;
	delete enemyPool;
	delete inputbox;
}