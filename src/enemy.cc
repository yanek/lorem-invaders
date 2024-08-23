#include "enemy.h"

#include "audio.h"
#include "colors.h"
#include "event_listener.h"
#include "inputbox.h"
#include "player.h"
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

void Enemy::draw() const
{
	const auto fntsize = static_cast<float>(res::font16.baseSize);

	Vector2 pos = position_;
	if (shake_ != nullptr)
	{
		pos.x += shake_->getOffset().x;
		pos.y += shake_->getOffset().y;
	}

	DrawTextEx(res::font16, value_.c_str(), pos, fntsize, 0, color::primary);
	DrawTextEx(res::font16, value_.substr(0, highlightOffset_).c_str(), pos, fntsize, 0, color::accent);
}

void Enemy::update(const GameScreen *screen, const float delta)
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

	if (isDying_)
	{
		return;
	}

	InputBox *inputBox = screen->getInputBox();

	position_.x += velocity_.x * delta;
	position_.y += velocity_.y * delta;

	const int matchval = inputBox->getMatch(value_);
	highlightOffset_ = matchval;

	if (matchval >= value_.length())
	{
		inputBox->clear();
		isDying_ = true;
		shake_ = new Shake(2, 100);
		Audio::play(res::SoundId::HIT);
		ScreenManager::getEventBus()->fire(EnemyKilledEvent(value_.length(), position_.y));
	}

	if (position_.y > Viewport::GAME_HEIGHT - 32)
	{
		despawn();
		ScreenManager::getEventBus()->fire(PlayerHurtEvent{});
	}
}