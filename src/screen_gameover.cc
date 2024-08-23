#include "screen_gameover.h"

#include "audio.h"
#include "colors.h"
#include "resources.h"
#include "screen_title.h"
#include "storage.h"
#include "viewport.h"

void GameOverScreen::init()
{
	Audio::play(res::SoundId::GAME_OVER);
	const int hiscore = LoadStorageData(storage::StorageData::HISCORE);
	if (score_ > hiscore)
	{
		SaveStorageData(storage::StorageData::HISCORE, score_);
	}
}

void GameOverScreen::update()
{
	if (IsKeyPressed(KEY_ENTER))
	{
		ScreenManager::changeToScreen(new TitleScreen);
	}
}

void GameOverScreen::draw()
{
	const auto fntsize = static_cast<float>(res::font16.baseSize);
	const auto score = TextFormat("SCORE: %010d", score_);
	const Vector2 scoresize = MeasureTextEx(res::font16, score, fntsize * 2, 0);
	const float scoreposX = Viewport::kGameWidth / 2.0f - scoresize.x / 2.0f;
	DrawTextEx(res::font16, score, Vector2{ scoreposX, 96 }, fntsize * 2, 0, color::primary);

	const auto title = "Game Over!";
	const Vector2 titlesize = MeasureTextEx(res::font16, title, fntsize, 0);
	const float titleposX = Viewport::kGameWidth / 2.0f - titlesize.x / 2.0f;
	DrawTextEx(res::font16, title, Vector2{ titleposX, 72 }, fntsize, 0, color::secondary);

	const auto action = "Press [ENTER] to return to title screen";
	const Vector2 actionsize = MeasureTextEx(res::font16, action, fntsize, 0);
	const float actionposX = Viewport::kGameWidth / 2.0f - actionsize.x / 2.0f;
	DrawTextEx(res::font16, action, Vector2{ actionposX, 134 }, fntsize, 0, color::secondary);
}

void GameOverScreen::unload()
{
}