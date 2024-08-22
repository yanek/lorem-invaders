#include "player.h"

#include "audio.h"
#include "colors.h"
#include "fx_flash.h"
#include "fx_shake.h"
#include "resources.h"
#include "screen.h"
#include "screen_game.h"
#include "screen_gameover.h"
#include "viewport.h"
#include <algorithm>
#include <raylib.h>
#include <string>

class InputBox;

void Player::Update(const float delta)
{
	if (mShake != nullptr)
	{
		mShake->Update(delta);
		if (mShake->ShouldDie())
		{
			delete mShake;
			mShake = nullptr;
		}
	}
}

void Player::DrawHud() const
{
	constexpr int size = 16;
	constexpr int gap = 4;

	DrawRectangle(0, 0, Viewport::kGameWidth, size + gap * 2, color::black);

	for (int i = 0; i < mMaxHitpoints; i++)
	{
		Rectangle dest = { static_cast<float>(gap + i * (size + gap)), gap, size, size };
		const Rectangle src = i < mHitpoints ? Rectangle{ 16, 0, size, size } : Rectangle{ 0, 0, size, size };

		if (mShake != nullptr)
		{
			dest.x += mShake->mOffset.x;
			dest.y += mShake->mOffset.y;
		}

		DrawTexturePro(res::textureHeart, src, dest, { 0, 0 }, 0, WHITE);
	}

	const int fntsize = res::font16.baseSize;
	const std::string score = TextFormat("%lu", mScore);
	const Vector2 scoreDimensions = MeasureTextEx(res::font16, score.c_str(), fntsize, 0);

	std::string scorePadding;
	for (int i = 0; i < 10 - score.length(); i++)
		scorePadding += "0";

	DrawTextEx(res::font16, scorePadding.c_str(), { Viewport::kGameWidth - 90 - gap, gap + 2 }, size, 0, color::background);
	DrawTextEx(res::font16, score.c_str(), { Viewport::kGameWidth - scoreDimensions.x - gap, gap + 2 }, size, 0, color::primary);
	DrawTextEx(res::font16, "SCORE", { Viewport::kGameWidth - gap - 140, gap + 2 }, size, 0, color::secondary);
}

void Player::Damage()
{
	mHitpoints = std::max(mHitpoints - 1, 0);

	InputBox *inputbox = static_cast<GameScreen *>(screenManager.GetCurrent())->GetInputBox();
	inputbox->mFlash = new Flash(color::accent, 30);
	inputbox->mShake = new Shake(4.0f, 100);
	mShake = new Shake(2.0f, 100);
	Audio::play(res::SoundId::HURT);

	if (IsDead())
	{
		screenManager.ChangeToScreen(new GameOverScreen{ mScore });
	}
}

bool Player::IsDead() const
{
	return mHitpoints == 0;
}

void Player::IncrementScore(const unsigned long baseValue, const float enemyVerticalPosition)
{
	float multiplier = 1.0f;

	if (enemyVerticalPosition > GameScreen::kScoreZone1)
	{
		multiplier = 1.5f;
	}
	else if (enemyVerticalPosition < GameScreen::kScoreZone2)
	{
		multiplier = 0.5f;
	}

	const float fscore = static_cast<float>(baseValue) * multiplier;
	mScore += static_cast<unsigned long>(fscore);
}
