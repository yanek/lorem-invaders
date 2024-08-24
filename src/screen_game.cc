#include "screen_game.h"

#include "audio.h"
#include "colors.h"
#include "enemy.h"
#include "enemy_pool.h"
#include "inputbox.h"
#include "player.h"
#include "resources.h"
#include "screen_title.h"
#include "viewport.h"
#include <raylib.h>

void GameScreen::init()
{
	constexpr Rectangle rect{
		5,
		Viewport::GAME_HEIGHT - 32 - 5,
		Viewport::GAME_WIDTH - 10,
		32
	};

	player_ = new Player{};
	inputBox_ = new InputBox{ rect };
	EnemyPool::init();
}

void GameScreen::update()
{
	const float delta = GetFrameTime();

	if (IsKeyPressed(KEY_ESCAPE))
	{
		isPaused_ = !isPaused_;
		Audio::play(SoundId::PAUSE);
	}

	if (isPaused_)
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

	EnemyPool::updateAll(this, delta);
	inputBox_->update(delta);
	player_->update(delta);

	spawnElapsed_ += delta;
	if (spawnElapsed_ > spawnTimeout_)
	{
		spawnElapsed_ = 0.0f;
		EnemyPool::spawn(lipsum_.next());
	}
}

void GameScreen::draw()
{
	const float delta = GetFrameTime();

	DrawRectangle(0, 0, Viewport::GAME_WIDTH, SCORE_ZONE_2, Fade(color::secondary, 0.1f));
	DrawRectangle(0, 0, Viewport::GAME_WIDTH, SCORE_ZONE_1, Fade(color::secondary, 0.2f));

	EnemyPool::drawAll();
	inputBox_->draw(delta);
	player_->draw();

	if (isPaused_)
	{
		DrawRectangle(0, 0, Viewport::GAME_WIDTH, Viewport::GAME_HEIGHT, Fade(color::black, 0.75f));
		DrawRectangle(0, 200, Viewport::GAME_WIDTH, 32, color::black);

		const Font *font = Resources::getFont();
		const auto paused = "PAUSE";
		const float psize = MeasureTextEx(*font, paused, font->baseSize, 0).x;
		const auto actions = "[Esc] Resume, [R] Restart, [B] Back to main menu";
		const float asize = MeasureTextEx(*font, actions, font->baseSize, 0).x;

		DrawTextEx(*font, paused, Vector2{ Viewport::GAME_WIDTH / 2.0f - psize / 2.0f, 209 }, font->baseSize, 0, color::white);
		DrawTextEx(*font, actions, Vector2{ Viewport::GAME_WIDTH / 2.0f - asize / 2.0f, 240 }, font->baseSize, 0, color::secondary);
	}
}

void GameScreen::unload()
{
	EnemyPool::close();
	delete player_;
	delete inputBox_;
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