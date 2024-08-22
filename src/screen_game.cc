#include "screen_game.h"

#include "colors.h"
#include "entity.h"
#include "inputbox.h"
#include "player.h"
#include "resources.h"
#include "screen_title.h"
#include "viewport.h"
#include <raylib.h>

GameScreen::GameScreen(const GameMode mode)
	: Screen("game_screen"), mLipsum{ mode }, mMode{ mode }
{
}

Player *GameScreen::GetPlayer() const
{
	return mPlayer;
}

EnemyPool *GameScreen::GetEnemyPool() const
{
	return mEnemyPool;
}

InputBox *GameScreen::GetInputBox() const
{
	return mInputBox;
}

void GameScreen::Init()
{
	mFramecounter = 0;

	constexpr Rectangle rect{
		5,
		Viewport::gameHeight - 32 - 5,
		Viewport::gameWidth - 10,
		32
	};

	mPlayer = new Player{};
	mInputBox = new InputBox{ rect };
	mEnemyPool = new EnemyPool{};
}

void GameScreen::Update()
{
	const float delta = GetFrameTime();

	if (IsKeyPressed(KEY_ESCAPE))
	{
		mIsPaused = !mIsPaused;
	}

	if (mIsPaused)
	{
		if (IsKeyPressed(KEY_R))
		{
			screenManager.ChangeToScreen(new GameScreen{ mMode });
		}

		if (IsKeyPressed(KEY_B))
		{
			screenManager.ChangeToScreen(new TitleScreen{});
		}

		return;
	}

	++mFramecounter;
	mEnemyPool->UpdateAll(this, delta);
	mInputBox->Update(delta);
	mPlayer->Update(delta);

	if (mFramecounter % 120 == 0)
	{
		mEnemyPool->Spawn(mLipsum.Next());
	}
}

void GameScreen::Draw()
{
	mEnemyPool->DrawAll();
	mInputBox->Draw(mFramecounter);
	mPlayer->DrawHud();

	if (mIsPaused)
	{
		DrawRectangle(0, 0, Viewport::gameWidth, Viewport::gameHeight, Fade(color::black, 0.75f));
		DrawRectangle(0, 200, Viewport::gameWidth, 32, color::black);

		const auto paused = "PAUSE";
		const float psize = MeasureTextEx(res::font16, paused, 16, 0).x;
		const auto actions = "[Esc] Resume, [R] Restart, [B] Back to main menu";
		const float asize = MeasureTextEx(res::font16, actions, 16, 0).x;

		DrawTextEx(res::font16, paused, Vector2{ Viewport::gameWidth / 2.0f - psize / 2.0f, 209 }, res::font16.baseSize, 0, color::white);
		DrawTextEx(res::font16, actions, Vector2{ Viewport::gameWidth / 2.0f - asize / 2.0f, 240 }, res::font16.baseSize, 0, color::secondary);
	}
}

void GameScreen::Unload()
{
	delete mPlayer;
	delete mEnemyPool;
	delete mInputBox;
}