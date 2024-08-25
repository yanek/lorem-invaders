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

void GameScreen::init()
{
	ScoreZone *zone1 = createEntity<ScoreZone>();
	zone1->setHeight(ScoreZone::ZONE_2);
	zone1->setAlpha(0.2f);

	ScoreZone *zone2 = createEntity<ScoreZone>();
	zone2->setHeight(ScoreZone::ZONE_1);
	zone2->setAlpha(0.1f);

	enemyPool_ = createEntity<EnemyPool>();
	createEntity<Player>();

	InputBox *ibox = createEntity<InputBox>();
	ibox->setRect({ 5,
	                Viewport::GAME_HEIGHT - 32 - 5,
	                Viewport::GAME_WIDTH - 10,
	                32 });

	enemyPool_->init();
}

void GameScreen::update(const f32 delta)
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
		enemyPool_->spawn(lipsum_.next());
	}
}

void GameScreen::draw(const f32 delta)
{

	if (isPaused())
	{
		DrawRectangle(0, 0, Viewport::GAME_WIDTH, Viewport::GAME_HEIGHT, Fade(color::black, 0.75f));
		DrawRectangle(0, 200, Viewport::GAME_WIDTH, 32, color::black);

		const Font *font   = Resources::getFont();
		const auto paused  = "PAUSE";
		const f32 psize    = MeasureTextEx(*font, paused, font->baseSize, 0).x;
		const auto actions = "[Esc] Resume, [R] Restart, [B] Back to main menu";
		const f32 asize    = MeasureTextEx(*font, actions, font->baseSize, 0).x;

		DrawTextEx(*font, paused, Vector2{ Viewport::GAME_WIDTH / 2.0f - psize / 2.0f, 209 }, font->baseSize, 0, color::white);
		DrawTextEx(*font, actions, Vector2{ Viewport::GAME_WIDTH / 2.0f - asize / 2.0f, 240 }, font->baseSize, 0, color::secondary);
	}
}

void GameScreen::unload()
{
	enemyPool_ = nullptr;
}

float GameScreen::getDifficultyModifier() const
{
	return difficultyModifier_;
}

void GameScreen::notify(const Event &event)
{
	if (event.getEventType() == EventType::EnemyKilled)
	{
		difficultyModifier_ = std::min(difficultyModifier_ + 0.01f, 9.0f);
		TraceLog(LOG_DEBUG, "Difficulty modifier: %f", difficultyModifier_);
	}
}