#include "enemy.h"

#include "audio.h"
#include "colors.h"
#include "enemy_pool.h"
#include "event_listener.h"
#include "inputbox.h"
#include "resources.h"
#include "viewport.h"
#include <raylib.h>

void Enemy::despawn()
{
	isActive_ = false;
	isDying_ = false;
	highlightOffset_ = 0;
	position_ = Vector2{ 0, 0 };
	velocity_ = Vector2{ 0, 0 };
}

void Enemy::draw(const f32 delta) const
{
	const Font *font = Resources::getFont();
	const auto fntsize = (float)font->baseSize;

	Vector2 pos = position_;
	if (shake_ != nullptr)
	{
		pos.x += shake_->getOffset().x;
		pos.y += shake_->getOffset().y;
	}

	const Color enemyColor = pattern_ != EnemyPattern::BONUS ? color::primary : color::secondary;
	DrawTextEx(*font, value_.c_str(), pos, fntsize, 0, enemyColor);
	DrawTextEx(*font, value_.substr(0, highlightOffset_).c_str(), pos, fntsize, 0, color::accent);
}

void Enemy::update(const f32 delta)
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
	for (i32 i = 0; (i < value_.length()) && (i < strlen(event.value)); ++i)
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
		shake_ = new Shake(2, 100);
		Audio::play(SoundId::HIT);
		ScreenManager::getEventBus()->fire(EnemyKilledEvent(value_.length(), position_.y));
	}
}