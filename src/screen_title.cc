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
	mMode = static_cast<GameMode>(LoadStorageData(storage::StorageData::MODE));
	mHiscore = LoadStorageData(storage::StorageData::HISCORE);
}

void TitleScreen::Init()
{
}

void TitleScreen::Update()
{
	if (IsKeyPressed(KEY_ENTER))
	{
		screenManager.ChangeToScreen(new GameScreen{ mMode });
	}

	if (IsKeyPressed(KEY_M))
	{
		mMode = static_cast<GameMode>((static_cast<int>(mMode) + 1) % static_cast<int>(GameMode::MODE_COUNT));
		SaveStorageData(storage::StorageData::MODE, static_cast<int>(mMode));
	}

	if (IsKeyPressed(KEY_ESCAPE))
	{

	}
}

void TitleScreen::Unload()
{
}

void TitleScreen::Draw()
{
	const auto fntsize = static_cast<float>(res::font16.baseSize);
	constexpr float halfwidth = Viewport::sGameWidth / 2.0f;

	const Texture2D *banner = &res::textureBanner;
	DrawTexture(*banner, halfwidth - banner->width / 2.0f, 32, color::white);

	const auto ver = "v0.4.2";
	const Vector2 versize = MeasureTextEx(res::font16, ver, fntsize, 0);
	DrawRectangle(355, 162, versize.x, versize.y, color::background);
	DrawTextEx(res::font16, ver, Vector2{ 355, 162 }, fntsize, 0, color::accent);

	const auto action = "* Press [ENTER] to start\n* Press [M] to change mode";
	const Vector2 actionsize = MeasureTextEx(res::font16, action, fntsize, 0);
	const float actionposX = halfwidth - actionsize.x / 2.0f;
	DrawTextEx(res::font16, action, Vector2{ actionposX, 200 }, fntsize, 0, color::secondary);

	const auto hiscorelabel = "HI-SCORE";
	const Vector2 hiscoresize = MeasureTextEx(res::font16, hiscorelabel, fntsize, 0);
	DrawTextEx(res::font16, hiscorelabel, Vector2{ halfwidth - hiscoresize.x / 2.0f, 400 }, fntsize, 0, color::secondary);

	const auto hiscoreval = TextFormat("%d", mHiscore);
	const Vector2 hiscorevalsize = MeasureTextEx(res::font16, hiscoreval, fntsize, 0);
	DrawTextEx(res::font16, hiscoreval, Vector2{ halfwidth - hiscorevalsize.x / 2.0f, 416 }, fntsize, 0, color::primary);

	std::string m;
	switch (mMode)
	{
	case GameMode::ENGLISH:
		m = "ENGLISH";
		break;
	default:
		m = "LOREM";
	}

	const auto mode = TextFormat("- %s MODE - ", m.c_str());
	const Vector2 modesize = MeasureTextEx(res::font16, mode, fntsize, 0);
	const float modeposX = Viewport::sGameWidth / 2.0f - modesize.x / 2.0f;
	DrawTextEx(res::font16, mode, Vector2{ modeposX, 264 }, fntsize, 0, color::primary);
}