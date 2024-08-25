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
	mode_    = (GameMode)loadStorageData(storage::StorageData::MODE);
	hiscore_ = loadStorageData(storage::StorageData::HISCORE);
}

void TitleScreen::init()
{
}

void TitleScreen::unload()
{
}

void TitleScreen::update(const f32 delta)
{
	if (bannerPosition_ < BANNER_ENDPOS)
	{
		bannerPosition_ = EaseBounceOut(animTime_, BANNER_STARTPOS, BANNER_ENDPOS - BANNER_STARTPOS, 3.0f);
		animTime_ += delta;
	}

	if (IsKeyPressed(KEY_ENTER))
	{
		Audio::play(SoundId::CLICK);
		ScreenManager::changeToScreen(new GameScreen{ mode_ });
	}

	if (IsKeyPressed(KEY_M))
	{
		Audio::play(SoundId::CLICK);
		mode_ = (GameMode)(((i32)mode_ + 1) % (int)GameMode::NUM_MODES);
		saveStorageData(storage::StorageData::MODE, (int)mode_);
	}
}

void TitleScreen::draw(const float delta)
{
	const Font *font              = Resources::getFont();
	const f32 fntsize             = (f32)font->baseSize;
	constexpr f32 HALF_GAME_WIDTH = Viewport::GAME_WIDTH / 2.0f;

	const Texture2D *banner = Resources::getTexture(TextureId::BANNER);
	DrawTexture(*banner, HALF_GAME_WIDTH - banner->width / 2.0f, bannerPosition_, color::white);

	const auto ver        = "v0.5.0";
	const Vector2 versize = MeasureTextEx(*font, ver, fntsize, 0);
	DrawRectangle(355, 162, versize.x, versize.y, color::background);
	DrawTextEx(*font, ver, Vector2{ 355, 162 }, fntsize, 0, color::accent);

	const auto action        = "* Press [ENTER] to start\n* Press [M] to change mode";
	const Vector2 actionsize = MeasureTextEx(*font, action, fntsize, 0);
	const f32 actionposX     = HALF_GAME_WIDTH - actionsize.x / 2.0f;
	DrawTextEx(*font, action, Vector2{ actionposX, 200 }, fntsize, 0, color::secondary);

	const auto hiscorelabel   = "HI-SCORE";
	const Vector2 hiscoresize = MeasureTextEx(*font, hiscorelabel, fntsize, 0);
	DrawTextEx(*font, hiscorelabel, Vector2{ HALF_GAME_WIDTH - hiscoresize.x / 2.0f, 400 }, fntsize, 0, color::secondary);

	const char *hiscoreval       = TextFormat("%d", hiscore_);
	const Vector2 hiscorevalsize = MeasureTextEx(*font, hiscoreval, fntsize, 0);
	DrawTextEx(*font, hiscoreval, Vector2{ HALF_GAME_WIDTH - hiscorevalsize.x / 2.0f, 416 }, fntsize, 0, color::primary);

	std::string m;
	switch (mode_)
	{
	case GameMode::ENGLISH:
		m = "ENGLISH";
		break;
	default:
		m = "LOREM";
	}

	const char *mode       = TextFormat("- %s MODE - ", m.c_str());
	const Vector2 modesize = MeasureTextEx(*font, mode, fntsize, 0);
	const f32 modeposX     = Viewport::GAME_WIDTH / 2.0f - modesize.x / 2.0f;
	DrawTextEx(*font, mode, Vector2{ modeposX, 264 }, fntsize, 0, color::primary);
}