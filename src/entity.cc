#include "entity.h"
#include "colors.h"
#include "inputbox.h"
#include "resources.h"
#include "viewport.h"
#include <raylib.h>
#include <vector>

size_t EnemyPool::Spawn(const std::string &value)
{
	const std::vector<Enemy> &pool = mPool;
	size_t id = pool.size();

	TraceLog(LOG_INFO, "Creating enemy: %i", id);

	// Find inactive Entity.
	for (size_t i = 0; i < pool.size(); ++i)
	{
		const Enemy &entity = pool[i];
		if (!entity.mActive)
		{
			id = i;
			break;
		}
	}

	if (id == pool.size())
	{
		mPool.emplace_back();
	}

	// Randomize horizontal position while making sure that the text does not overflow the viewport.
	const float txtsize = MeasureTextEx(res::font16, value.c_str(), res::font16.baseSize, 0).x;
	const float posx = GetRandomValue(0, Viewport::gameWidth - txtsize);

	Enemy &entity = mPool[id];
	entity.mId = id;
	entity.mPosition = Vector2{ posx, 0.0f };
	entity.mVelocity = Vector2{ 0, 100 };
	entity.mValue = value;
	entity.mActive = true;

	return id;
}

Enemy &EnemyPool::Get(const size_t id)
{
	return mPool[id];
}

size_t EnemyPool::Count() const
{
	return mPool.size();
}

void EnemyPool::UpdateAll(const GameScreen *screen, const float delta)
{
	for (auto &entity : mPool)
	{
		if (entity.mActive)
		{
			entity.Update(screen, delta);
		}
	}
}

void EnemyPool::DrawAll() const
{
	for (const auto &entity : mPool)
	{
		if (entity.mActive)
		{
			entity.Draw();
		}
	}
}

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
		pos.x += mShake->offset.x;
		pos.y += mShake->offset.y;
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

	InputBox *inputBox = screen->GetInputBox();
	Player *player = screen->GetPlayer();

	mPosition.x += mVelocity.x * delta;
	mPosition.y += mVelocity.y * delta;

	const int matchval = inputBox->GetMatch(mValue);
	mHighlightOffset = matchval;

	if (matchval >= mValue.length())
	{
		inputBox->Clear();
		player->IncrementScore(mValue.length());
		mIsDying = true;
		mShake = new Shake(2, 100);
	}

	if (mPosition.y > Viewport::gameHeight - 32)
	{
		player->Damage();
		Despawn();
	}
}