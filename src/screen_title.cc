#include "screen_title.h"

#include "audio.h"
#include "colors.h"
#include "resources.h"
#include "screen_game.h"
#include "storage.h"
#include "viewport.h"
#include <raylib.h>
#include <reasing.h>

TitleScreen::TitleScreen()
{
	mode_ = (GameMode)loadStorageData(storage::StorageData::MODE);
	hiscore_ = loadStorageData(storage::StorageData::HISCORE);
}

void TitleScreen::init()
{
}

void TitleScreen::update()
{
	if (bannerPosition_ < BANNER_ENDPOS)
	{
		bannerPosition_ = EaseBounceOut(animTime_, BANNER_STARTPOS, BANNER_ENDPOS - BANNER_STARTPOS, 3.0f);
		animTime_ += GetFrameTime();
	}

	if (IsKeyPressed(KEY_ENTER))
	{
		Audio::play(SoundId::CLICK);
		ScreenManager::changeToScreen(new GameScreen{ mode_ });
	}

	if (IsKeyPressed(KEY_M))
	{
		Audio::play(SoundId::CLICK);
		mode_ = static_cast<GameMode>(((int)mode_ + 1) % (int)GameMode::NUM_MODES);
		saveStorageData(storage::StorageData::MODE, (int)mode_);
	}
}

void TitleScreen::unload()
{
}

void TitleScreen::draw()
{
	const Font *font = Resources::getFont();
	const auto fntsize = (float)font->baseSize;
	constexpr float halfwidth = Viewport::GAME_WIDTH / 2.0f;

	const Texture2D *banner = Resources::getTexture(TextureId::BANNER);
	DrawTexture(*banner, halfwidth - banner->width / 2.0f, bannerPosition_, color::white);

	const auto ver = "v0.5.0";
	const Vector2 versize = MeasureTextEx(*font, ver, fntsize, 0);
	DrawRectangle(355, 162, versize.x, versize.y, color::background);
	DrawTextEx(*font, ver, Vector2{ 355, 162 }, fntsize, 0, color::accent);

	const auto action = "* Press [ENTER] to start\n* Press [M] to change mode";
	const Vector2 actionsize = MeasureTextEx(*font, action, fntsize, 0);
	const float actionposX = halfwidth - actionsize.x / 2.0f;
	DrawTextEx(*font, action, Vector2{ actionposX, 200 }, fntsize, 0, color::secondary);

	const auto hiscorelabel = "HI-SCORE";
	const Vector2 hiscoresize = MeasureTextEx(*font, hiscorelabel, fntsize, 0);
	DrawTextEx(*font, hiscorelabel, Vector2{ halfwidth - hiscoresize.x / 2.0f, 400 }, fntsize, 0, color::secondary);

	const auto hiscoreval = TextFormat("%d", hiscore_);
	const Vector2 hiscorevalsize = MeasureTextEx(*font, hiscoreval, fntsize, 0);
	DrawTextEx(*font, hiscoreval, Vector2{ halfwidth - hiscorevalsize.x / 2.0f, 416 }, fntsize, 0, color::primary);

	std::string m;
	switch (mode_)
	{
	case GameMode::ENGLISH:
		m = "ENGLISH";
		break;
	default:
		m = "LOREM";
	}

	const auto mode = TextFormat("- %s MODE - ", m.c_str());
	const Vector2 modesize = MeasureTextEx(*font, mode, fntsize, 0);
	const float modeposX = Viewport::GAME_WIDTH / 2.0f - modesize.x / 2.0f;
	DrawTextEx(*font, mode, Vector2{ modeposX, 264 }, fntsize, 0, color::primary);
}