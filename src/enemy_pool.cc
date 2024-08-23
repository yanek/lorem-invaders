#include "enemy_pool.h"

#include "resources.h"
#include "viewport.h"
#include <cassert>

Enemy *EnemyPool::pool_[MAX_POOLED];
bool EnemyPool::isReady_ = false;

void EnemyPool::init()
{
	for (int i = 0; i < MAX_POOLED; ++i)
	{
		pool_[i] = new Enemy();
	}
}

void EnemyPool::close()
{
	for (int i = 0; i < MAX_POOLED; ++i)
	{
		delete pool_[i];
	}
}

Enemy *EnemyPool::spawn(const std::string &value)
{
	assert(isReady_);

	int id = -1;

	// Find inactive enemy.
	for (int i = 0; i < MAX_POOLED; ++i)
	{
		if (!pool_[i]->mActive)
		{
			id = i;
			break;
		}
	}

	TraceLog(LOG_INFO, "Creating enemy: %i", id);

	// Randomize horizontal position while making sure that the text does not overflow the viewport.
	const float txtsize = MeasureTextEx(res::font16, value.c_str(), res::font16.baseSize, 0).x;
	const float posx = GetRandomValue(0, Viewport::kGameWidth - txtsize);

	Enemy *enemy = pool_[id];
	enemy->mId = id;
	enemy->mPosition = Vector2{ posx, 0.0f };
	enemy->mVelocity = Vector2{ 0, 100 };
	enemy->mValue = value;
	enemy->mActive = true;

	return enemy;
}

Enemy *EnemyPool::getEnemy(const int id)
{
	return pool_[id];
}

void EnemyPool::updateAll(const GameScreen *screen, const float delta)
{
	assert(_isReady);
	for (auto *entity : pool_)
	{
		if (entity->mActive) entity->Update(screen, delta);
	}
}

void EnemyPool::drawAll()
{
	assert(_isReady);
	for (const auto *entity : pool_)
	{
		if (entity->mActive) entity->Draw();
	}
}