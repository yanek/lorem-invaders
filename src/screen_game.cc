#include "screen_game.h"

#include "audio.h"
#include "colors.h"
#include "enemy.h"
#include "enemy_pool.h"
#include "inputbox.h"
#include "player.h"
#include "resources.h"
#include "score_zone.h"
#include "screen_title.h"
#include "viewport.h"
#include <raylib.h>

static float mapRange(float value);

void GameScreen::init()
{
	auto *zone1 = createEntity<ScoreZone>();
	zone1->setHeight(ScoreZone::ZONE_2);
	zone1->setAlpha(0.2f);

	auto *zone2 = createEntity<ScoreZone>();
	zone2->setHeight(ScoreZone::ZONE_1);
	zone2->setAlpha(0.1f);

	enemyPool_ = createEntity<EnemyPool>();
	createEntity<Player>();

	auto *ibox = createEntity<InputBox>();
	ibox->setRect({ 5,
	                Viewport::GAME_HEIGHT - 32 - 5,
	                Viewport::GAME_WIDTH - 10,
	                32 });

	enemyPool_->init();
}

void GameScreen::update(const float delta)
{
	if (IsKeyPressed(KEY_ESCAPE))
	{
		setPaused(!isPaused());
		Audio::play(SoundId::PAUSE);
	}

	if (isPaused())
	{
		if (IsKeyPressed(KEY_R))
		{
			Audio::play(SoundId::CLICK);
			ScreenManager::changeToScreen(new GameScreen{ gameMode_ });
		}

		if (IsKeyPressed(KEY_B))
		{
			Audio::play(SoundId::CLICK);
			ScreenManager::changeToScreen(new TitleScreen{});
		}

		return;
	}

	spawnElapsed_ += delta;
	if (spawnElapsed_ > spawnTimeout_)
	{
		spawnElapsed_ = 0.0f;
		enemyPool_->spawn(lipsum_);
		spawnTimeout_ = mapRange(difficultyModifier_);
		TraceLog(LOG_DEBUG, "Spawn timeout: %f", spawnTimeout_);
	}
}

void GameScreen::draw(const float delta)
{

	if (isPaused())
	{
		DrawRectangle(0, 0, Viewport::GAME_WIDTH, Viewport::GAME_HEIGHT, Fade(color::black, 0.75f));
		DrawRectangle(0, 200, Viewport::GAME_WIDTH, 32, color::black);

		const Font *font   = Resources::getFont();
		const auto fntsize = (float)font->baseSize;
		const auto paused  = "PAUSE";
		const float psize  = MeasureTextEx(*font, paused, fntsize, 0).x;
		const auto actions = "[Esc] Resume, [R] Restart, [B] Back to main menu";
		const float asize  = MeasureTextEx(*font, actions, fntsize, 0).x;

		Vector2 drawPos;
		drawPos = Vector2{ Viewport::GAME_WIDTH / 2.0f - psize / 2.0f, 209 };
		DrawTextEx(*font, paused, drawPos, fntsize, 0, color::white);

		drawPos = Vector2{ Viewport::GAME_WIDTH / 2.0f - asize / 2.0f, 240 };
		DrawTextEx(*font, actions, drawPos, fntsize, 0, color::secondary);
	}
}

void GameScreen::unload()
{
	enemyPool_ = nullptr;
}

void GameScreen::notify(const Event &event)
{
	if (event.getEventType() == EventType::EnemyKilled)
	{
		difficultyModifier_ = std::min(difficultyModifier_ + 0.05f, 10.0f);
		TraceLog(LOG_DEBUG, "Difficulty modifier: %f", difficultyModifier_);
	}
}

static float mapRange(float value)
{
	constexpr float IN_MIN  = 1.0f;
	constexpr float IN_MAX  = 10.0f;
	constexpr float OUT_MIN = 3.0f;
	constexpr float OUT_MAX = 1.0f;
	return OUT_MIN + (value - IN_MIN) * (OUT_MAX - OUT_MIN) / (IN_MAX - IN_MIN);
}