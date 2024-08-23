#include "player.h"

#include "audio.h"
#include "colors.h"
#include "fx_shake.h"
#include "inputbox.h"
#include "resources.h"
#include "screen.h"
#include "screen_game.h"
#include "screen_gameover.h"
#include "viewport.h"
#include <algorithm>
#include <raylib.h>
#include <string>

class InputBox;

void Player::update(const float delta)
{
	if (shake_ != nullptr)
	{
		shake_->update(delta);
		if (shake_->shouldDie())
		{
			delete shake_;
			shake_ = nullptr;
		}
	}
}

void Player::draw() const
{
	constexpr int size = 16;
	constexpr int gap = 4;

	DrawRectangle(0, 0, Viewport::GAME_WIDTH, size + gap * 2, color::black);

	for (int i = 0; i < maxHitpoints_; i++)
	{
		Rectangle dest = { static_cast<float>(gap + i * (size + gap)), gap, size, size };
		const Rectangle src = i < hitpoints_ ? Rectangle{ 16, 0, size, size } : Rectangle{ 0, 0, size, size };

		if (shake_ != nullptr)
		{
			dest.x += shake_->getOffset().x;
			dest.y += shake_->getOffset().y;
		}

		DrawTexturePro(res::textureHeart, src, dest, { 0, 0 }, 0, WHITE);
	}

	const int fntsize = res::font16.baseSize;
	const std::string score = TextFormat("%lu", score_);
	const Vector2 scoreDimensions = MeasureTextEx(res::font16, score.c_str(), fntsize, 0);

	std::string scorePadding;
	for (int i = 0; i < 10 - score.length(); i++)
		scorePadding += "0";

	DrawTextEx(res::font16, scorePadding.c_str(), { Viewport::GAME_WIDTH - 90 - gap, gap + 2 }, size, 0, color::background);
	DrawTextEx(res::font16, score.c_str(), { Viewport::GAME_WIDTH - scoreDimensions.x - gap, gap + 2 }, size, 0, color::primary);
	DrawTextEx(res::font16, "SCORE", { Viewport::GAME_WIDTH - gap - 140, gap + 2 }, size, 0, color::secondary);
}

void Player::damage()
{
	hitpoints_ = std::max(hitpoints_ - 1, 0);
	shake_ = new Shake(2.0f, 100);
	Audio::play(res::SoundId::HURT);

	if (isDead())
	{
		ScreenManager::changeToScreen(new GameOverScreen{ score_ });
	}
}

void Player::notify(const Event &event)
{
	if (event.getEventType() == EventType::EnemyKilled)
	{
		const auto ev = (const EnemyKilledEvent &)event;

		const float score = ev.letterCount * 10;
		float positionMultiplier = 1.0f;

		if (ev.verticalPosition > GameScreen::SCORE_ZONE_1)
			positionMultiplier = 1.5f;
		else if (ev.verticalPosition < GameScreen::SCORE_ZONE_2)
			positionMultiplier = 0.5f;

		score_ += (unsigned long)(score * positionMultiplier);
	}

	if (event.getEventType() == EventType::PlayerHurt)
	{
		damage();
	}
}
