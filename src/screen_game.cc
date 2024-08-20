#include "entity.h"
#include "inputbox.h"
#include "screens.h"
#include "viewport.h"
#include <raylib.h>

void GameScreen::Init()
{
	framecounter = 0;

	constexpr Rectangle rect{
		5,
		Viewport::gameHeight - 32 - 5,
		Viewport::gameWidth - 10,
		32
	};

	this->inputbox = new InputBox{ rect };
	this->enemyPool = new EnemyPool{};

}

void GameScreen::Update()
{
	++framecounter;
	this->enemyPool->UpdateAll();
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
}

void GameScreen::Unload()
{
	delete enemyPool;
	delete inputbox;
}