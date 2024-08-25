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

void Player::draw(const float delta) const
{
	constexpr int SIZE = 16;
	constexpr int GAP  = 4;

	DrawRectangle(0, 0, Viewport::GAME_WIDTH, SIZE + GAP * 2, color::black);

	for (int i = 0; i < maxHitpoints_; i++)
	{
		Rectangle dest      = { static_cast<float>(GAP + i * (SIZE + GAP)), GAP, SIZE, SIZE };
		const Rectangle src = i < hitpoints_ ? Rectangle{ 16, 0, SIZE, SIZE } : Rectangle{ 0, 0, SIZE, SIZE };

		if (shake_ != nullptr)
		{
			dest.x += shake_->getOffset().x;
			dest.y += shake_->getOffset().y;
		}

		const Texture2D *tex = Resources::getTexture(TextureId::HEART);
		DrawTexturePro(*tex, src, dest, { 0, 0 }, 0, WHITE);
	}

	const Font *font              = Resources::getFont();
	const int fntsize             = font->baseSize;
	const std::string score       = TextFormat("%lu", score_);
	const Vector2 scoreDimensions = MeasureTextEx(*font, score.c_str(), fntsize, 0);

	std::string scorePadding;
	for (int i = 0; i < 10 - score.length(); i++)
		scorePadding += "0";

	DrawTextEx(*font, scorePadding.c_str(), { Viewport::GAME_WIDTH - 90 - GAP, GAP + 2 }, SIZE, 0, color::background);
	DrawTextEx(*font, score.c_str(), { Viewport::GAME_WIDTH - scoreDimensions.x - GAP, GAP + 2 }, SIZE, 0, color::primary);
	DrawTextEx(*font, "SCORE", { Viewport::GAME_WIDTH - GAP - 140, GAP + 2 }, SIZE, 0, color::secondary);
}

void Player::damage()
{
	hitpoints_ = std::max(hitpoints_ - 1, 0);
	TraceLog(LOG_DEBUG, "Player (0x%X) damaged! HP: %i/%i", this, hitpoints_, maxHitpoints_);
	shake_ = new Shake(2.0f, 100);
	Audio::play(SoundId::HURT);

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

		const float score        = ev.letterCount * 10;
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
