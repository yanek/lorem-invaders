#include "colors.h"
#include "resources.h"
#include "screens.h"
#include "storage.h"
#include "viewport.h"

GameOverScreen::GameOverScreen(const unsigned long score)
	: Screen("gameover_screen"), score(score)
{
}

void GameOverScreen::Init()
{
	const int hiscore = LoadStorageData(storage::StorageData::HISCORE);
	if (this->score > hiscore)
	{
		SaveStorageData(storage::StorageData::HISCORE, this->score);
	}
}

void GameOverScreen::Update()
{
	if (IsKeyPressed(KEY_ENTER))
	{
		screenManager.ChangeToScreen(new TitleScreen);
	}
}

void GameOverScreen::Draw()
{
	const auto fntsize = static_cast<float>(res::font16.baseSize);
	const auto score = TextFormat("SCORE: %010d", this->score);
	const Vector2 scoresize = MeasureTextEx(res::font16, score, fntsize * 2, 0);
	const float scoreposX = Viewport::gameWidth / 2.0f - scoresize.x / 2.0f;
	DrawTextEx(res::font16, score, Vector2{ scoreposX, 96 }, fntsize * 2, 0, color::white);

	const auto title = "Game Over!";
	const Vector2 titlesize = MeasureTextEx(res::font16, title, fntsize, 0);
	const float titleposX = Viewport::gameWidth / 2.0f - titlesize.x / 2.0f;
	DrawTextEx(res::font16, title, Vector2{ titleposX, 72 }, fntsize, 0, color::gray);

	const auto action = "Press [ENTER] to return to title screen";
	const Vector2 actionsize = MeasureTextEx(res::font16, action, fntsize, 0);
	const float actionposX = Viewport::gameWidth / 2.0f - actionsize.x / 2.0f;
	DrawTextEx(res::font16, action, Vector2{ actionposX, 134 }, fntsize, 0, color::gray);
}

void GameOverScreen::Unload()
{
}