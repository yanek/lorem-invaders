#include "screen_title.h"
#include "colors.h"
#include "resources.h"
#include "screen_game.h"
#include "storage.h"
#include "viewport.h"
#include <raylib.h>

TitleScreen::TitleScreen()
	: Screen("title_screen")
{
	this->mode = static_cast<GameMode>(LoadStorageData(storage::StorageData::MODE));
	this->hiscore = LoadStorageData(storage::StorageData::HISCORE);
}

void TitleScreen::Init()
{
}

void TitleScreen::Update()
{
	if (IsKeyPressed(KEY_ENTER))
	{
		screenManager.ChangeToScreen(new GameScreen{ this->mode });
	}

	if (IsKeyPressed(KEY_M))
	{
		this->mode = static_cast<GameMode>((static_cast<int>(this->mode) + 1) % static_cast<int>(GameMode::MODE_COUNT));
		SaveStorageData(storage::StorageData::MODE, static_cast<int>(this->mode));
	}
}

void TitleScreen::Unload()
{
}

void TitleScreen::Draw()
{
	const auto fntsize = static_cast<float>(res::font16.baseSize);
	const auto title = "Lorem Invader";
	const Vector2 titlesize = MeasureTextEx(res::font16, title, fntsize * 2, 0);
	const float titleposX = Viewport::gameWidth / 2.0f - titlesize.x / 2.0f;
	DrawTextEx(res::font16, title, Vector2{ titleposX, 72 }, fntsize * 2, 0, color::primary);

	const auto ver = "v0.4.1";
	const Vector2 versize = MeasureTextEx(res::font16, ver, fntsize, 0);
	DrawRectangle(titleposX + titlesize.x - versize.x, 96, versize.x, versize.y, color::background);
	DrawTextEx(res::font16, ver, Vector2{ titleposX + titlesize.x - versize.x, 96 }, fntsize, 0, color::accent);

	const auto action = "* Press [ENTER] to start\n* Press [M] to change mode";
	const Vector2 actionsize = MeasureTextEx(res::font16, action, fntsize, 0);
	const float actionposX = Viewport::gameWidth / 2.0f - actionsize.x / 2.0f;
	DrawTextEx(res::font16, action, Vector2{ actionposX, 128 }, fntsize, 0, color::secondary);

	const auto hiscore = TextFormat("Hi-Score: %d", this->hiscore);
	DrawTextEx(res::font16, hiscore, Vector2{ 8, Viewport::gameHeight - fntsize - 2 }, fntsize, 0, color::primary);

	std::string m;

	switch (this->mode)
	{
	case GameMode::ENGLISH:
		m = "ENGLISH";
		break;
	default:
		m = "LOREM";
	}

	const auto mode = TextFormat("- %s MODE - ", m.c_str());
	const Vector2 modesize = MeasureTextEx(res::font16, mode, fntsize, 0);
	const float modeposX = Viewport::gameWidth / 2.0f - modesize.x / 2.0f;
	DrawTextEx(res::font16, mode, Vector2{ modeposX, 200 }, fntsize, 0, color::primary);
}