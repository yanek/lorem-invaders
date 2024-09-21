#include "enemy.h"

#include "audio.h"
#include "colors.h"
#include "enemy_pool.h"
#include "event_listener.h"
#include "inputbox.h"
#include "raymath.h"
#include "resources.h"
#include "viewport.h"
#include <raylib.h>

static Rectangle calculateBounds(const Vector2 &position, const char *value);

void Enemy::despawn()
{
	isActive_        = false;
	isDying_         = false;
	highlightOffset_ = 0;
	position_        = Vector2{ 0, 0 };
	velocity_        = Vector2{ 0, 0 };
}

void Enemy::draw(const float delta) const
{
	const Font *font   = Resources::getFont();
	const auto fntsize = (float)font->baseSize;

	Vector2 pos = { bounds_.x, bounds_.y };
	if (shake_ != nullptr)
	{
		pos.x += shake_->getOffset().x;
		pos.y += shake_->getOffset().y;
	}

	const Color enemyColor = pattern_ != EnemyPattern::BONUS ? color::primary : color::secondary;
	DrawTextEx(*font, value_.c_str(), pos, fntsize, 0, enemyColor);
	DrawTextEx(*font, value_.substr(0, highlightOffset_).c_str(), pos, fntsize, 0, color::accent);

#ifdef DEBUG_DRAW_ENABLED
	DrawPixel((int)position_.x, (int)position_.y, MAGENTA);
	DrawRectangleLinesEx(bounds_, 1, SKYBLUE);
#endif
}

void Enemy::update(const float delta)
{
	// If the entity is shaking, it must be dying.
	if (shake_ != nullptr)
	{
		shake_->update(delta);
		if (shake_->shouldDie())
		{
			delete shake_;
			shake_ = nullptr;
			despawn(); // Despawn the entity after the shake animation.
		}
	}

	if (isDying_) return;

	position_.x += velocity_.x * delta;
	position_.y += velocity_.y * delta;
	bounds_ = calculateBounds(position_, value_.c_str());

	// Check if the enemy is out of bounds.
	if (position_.y > Viewport::GAME_HEIGHT - 32 || position_.x < 0 || position_.x > Viewport::GAME_WIDTH)
	{
		despawn();
		if (pattern_ != EnemyPattern::BONUS)
			ScreenManager::getEventBus()->fire(PlayerHurtEvent{});
	}
}

void Enemy::notify(const Event &event)
{
	if (!isActive_) return;

	if (event.getEventType() == EventType::InputUpdated)
	{
		onInputUpdate((const InputUpdatedEvent &)event);
	}
}

void Enemy::onInputUpdate(const InputUpdatedEvent &event)
{
	int matchCount = 0;

	// Check if the input matches the value of the enemy.
	// If it does, increment the match count.
	for (int i = 0; (i < value_.length()) && (i < strlen(event.value)); ++i)
	{
		if (event.value[i] == value_[i])
		{
			matchCount++;
		}
		else
		{
			matchCount = 0;
			break;
		}
	}

	highlightOffset_ = matchCount;

	if (matchCount >= value_.length())
	{
		isDying_ = true;
		shake_   = new Shake(2, 100);
		Audio::play(SoundId::HIT);
		ScreenManager::getEventBus()->fire(EnemyKilledEvent(value_.length(), position_.y));

		if (pattern_ == EnemyPattern::BONUS)
		{
			ScreenManager::getEventBus()->fire(PlayerHealedEvent{});
		}
	}
}

Rectangle calculateBounds(const Vector2 &position, const char *value)
{
	const Font *fnt       = Resources::getFont();
	const auto fntsize    = (float)fnt->baseSize;
	const Vector2 txtsize = MeasureTextEx(*fnt, value, fntsize, 0);
	const Vector2 hlfsize = Vector2Scale(txtsize, 0.5f);
	const Vector2 pos     = Vector2Subtract(position, hlfsize);
	return { pos.x, pos.y, txtsize.x, txtsize.y };
}