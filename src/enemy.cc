#include "enemy.h"

#include "audio.h"
#include "colors.h"
#include "event_dispatcher.h"
#include "inputbox.h"
#include "player.h"
#include "resources.h"
#include "viewport.h"
#include <raylib.h>

void Enemy::Despawn()
{
	mActive = false;
	mIsDying = false;
	mHighlightOffset = 0;
	mAlpha = 255;
	mPosition = Vector2{ 0, 0 };
	mVelocity = Vector2{ 0, 0 };
}

void Enemy::Draw() const
{
	const auto fntsize = static_cast<float>(res::font16.baseSize);

	Vector2 pos = mPosition;
	if (mShake != nullptr)
	{
		pos.x += mShake->mOffset.x;
		pos.y += mShake->mOffset.y;
	}

	DrawTextEx(res::font16, mValue.c_str(), pos, fntsize, 0, color::primary);
	DrawTextEx(res::font16, mValue.substr(0, mHighlightOffset).c_str(), pos, fntsize, 0, color::accent);
}

void Enemy::Update(const GameScreen *screen, const float delta)
{
	// If the entity is shaking, it must be dying.
	if (mShake != nullptr)
	{
		mShake->Update(delta);
		if (mShake->ShouldDie())
		{
			delete mShake;
			mShake = nullptr;
			Despawn(); // Despawn the entity after the shake animation.
		}
	}

	if (mIsDying)
	{
		return;
	}

	InputBox *inputBox = screen->getInputBox();
	Player *player = screen->getPlayer();

	mPosition.x += mVelocity.x * delta;
	mPosition.y += mVelocity.y * delta;

	const int matchval = inputBox->GetMatch(mValue);
	mHighlightOffset = matchval;

	if (matchval >= mValue.length())
	{
		inputBox->Clear();
		player->IncrementScore(mValue.length() * 10, mPosition.y);
		mIsDying = true;
		mShake = new Shake(2, 100);
		ScreenManager::getEventBus()->fire(EnemyKilledEvent(mValue.length(), mPosition.y));
		Audio::play(res::SoundId::HIT);
	}

	if (mPosition.y > Viewport::kGameHeight - 32)
	{
		player->Damage();
		Despawn();
	}
}