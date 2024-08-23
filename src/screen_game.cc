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

Player *GameScreen::getPlayer() const
{
	return player_;
}

InputBox *GameScreen::getInputBox() const
{
	return inputBox_;
}

void GameScreen::init()
{
	constexpr Rectangle rect{
		5,
		Viewport::kGameHeight - 32 - 5,
		Viewport::kGameWidth - 10,
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
		Audio::play(res::SoundId::PAUSE);
	}

	if (isPaused_)
	{
		if (IsKeyPressed(KEY_R))
		{
			Audio::play(res::SoundId::CLICK);
			ScreenManager::changeToScreen(new GameScreen{ gameMode_ });
		}

		if (IsKeyPressed(KEY_B))
		{
			Audio::play(res::SoundId::CLICK);
			ScreenManager::changeToScreen(new TitleScreen{});
		}

		return;
	}

	EnemyPool::updateAll(this, delta);
	inputBox_->Update(delta);
	player_->Update(delta);

	spawnElapsed_ += delta;
	if (spawnElapsed_ > spawnTimeout_)
	{
		spawnElapsed_ = 0.0f;
		EnemyPool::spawn(lipsum_.Next());
	}
}

void GameScreen::draw()
{
	const float delta = GetFrameTime();

	DrawRectangle(0, 0, Viewport::kGameWidth, SCORE_ZONE_2, Fade(color::secondary, 0.1f));
	DrawRectangle(0, 0, Viewport::kGameWidth, SCORE_ZONE_1, Fade(color::secondary, 0.2f));

	EnemyPool::drawAll();
	inputBox_->Draw(delta);
	player_->DrawHud();

	if (isPaused_)
	{
		DrawRectangle(0, 0, Viewport::kGameWidth, Viewport::kGameHeight, Fade(color::black, 0.75f));
		DrawRectangle(0, 200, Viewport::kGameWidth, 32, color::black);

		const auto paused = "PAUSE";
		const float psize = MeasureTextEx(res::font16, paused, 16, 0).x;
		const auto actions = "[Esc] Resume, [R] Restart, [B] Back to main menu";
		const float asize = MeasureTextEx(res::font16, actions, 16, 0).x;

		DrawTextEx(res::font16, paused, Vector2{ Viewport::kGameWidth / 2.0f - psize / 2.0f, 209 }, res::font16.baseSize, 0, color::white);
		DrawTextEx(res::font16, actions, Vector2{ Viewport::kGameWidth / 2.0f - asize / 2.0f, 240 }, res::font16.baseSize, 0, color::secondary);
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