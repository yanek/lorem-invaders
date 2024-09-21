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

void TitleScreen::update(const float delta)
{
	if (bannerPosition_ < BANNER_ENDPOS)
	{
		bannerPosition_ = (int)EaseBounceOut(animTime_, BANNER_STARTPOS, BANNER_ENDPOS - BANNER_STARTPOS, 3.0f);
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
		mode_ = (GameMode)(((unsigned char)mode_ + 1) % (unsigned char)GameMode::NUM_MODES);
		saveStorageData(storage::StorageData::MODE, (unsigned char)mode_);
	}
}

void TitleScreen::draw(const float delta)
{
	const Font *font                = Resources::getFont();
	const auto fntsize              = (float)font->baseSize;
	constexpr float HALF_GAME_WIDTH = Viewport::GAME_WIDTH * 0.5f;

	const Texture2D *banner = Resources::getTexture(TextureId::BANNER);
	DrawTexture(*banner, (int)HALF_GAME_WIDTH - banner->width / 2, bannerPosition_, color::white);

	const char *ver       = TextFormat("v%d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
	const Vector2 versize = MeasureTextEx(*font, ver, fntsize, 0);
	DrawRectangle(355, 162, (int)versize.x, (int)versize.y, color::background);
	DrawTextEx(*font, ver, Vector2{ 355, 162 }, fntsize, 0, color::accent);

	const auto action        = "* Press [ENTER] to start\n* Press [M] to change mode";
	const Vector2 actionsize = MeasureTextEx(*font, action, fntsize, 0);
	const float actionposX   = HALF_GAME_WIDTH - actionsize.x / 2.0f;
	DrawTextEx(*font, action, Vector2{ actionposX, 200 }, fntsize, 0, color::secondary);

	const auto hiscorelabel   = "HI-SCORE";
	const Vector2 hiscoresize = MeasureTextEx(*font, hiscorelabel, fntsize, 0);
	DrawTextEx(*font, hiscorelabel, Vector2{ HALF_GAME_WIDTH - hiscoresize.x / 2.0f, 400 }, fntsize, 0, color::secondary);

	const char *hiscoreval       = TextFormat("%d", hiscore_);
	const Vector2 hiscorevalsize = MeasureTextEx(*font, hiscoreval, fntsize, 0);
	DrawTextEx(*font, hiscoreval, Vector2{ HALF_GAME_WIDTH - hiscorevalsize.x / 2.0f, 416 }, fntsize, 0, color::primary);

	String m;
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
	const float modeposX   = Viewport::GAME_WIDTH / 2.0f - modesize.x / 2.0f;
	DrawTextEx(*font, mode, Vector2{ modeposX, 264 }, fntsize, 0, color::primary);
}