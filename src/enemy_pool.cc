#include "enemy_pool.h"

#include "resources.h"
#include "viewport.h"
#include <cassert>

Enemy *EnemyPool::pool_[MAX_POOLED];

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
	int id = -1;

	// Find inactive enemy.
	for (int i = 0; i < MAX_POOLED; ++i)
	{
		if (!pool_[i]->isActive_)
		{
			id = i;
			break;
		}
	}

	TraceLog(LOG_INFO, "Creating enemy: %i", id);

	// Randomize horizontal position while making sure that the text does not overflow the viewport.
	const float txtsize = MeasureTextEx(res::font16, value.c_str(), res::font16.baseSize, 0).x;
	const float posx = GetRandomValue(0, Viewport::GAME_WIDTH - txtsize);

	Enemy *enemy = pool_[id];
	enemy->id_ = id;
	enemy->position_ = Vector2{ posx, 0.0f };
	enemy->velocity_ = Vector2{ 0, 100 };
	enemy->value_ = value;
	enemy->isActive_ = true;

	return enemy;
}

Enemy *EnemyPool::getEnemy(const int id)
{
	return pool_[id];
}

void EnemyPool::updateAll(const GameScreen *screen, const float delta)
{
	for (auto *entity : pool_)
	{
		if (entity->isActive_) entity->update(screen, delta);
	}
}

void EnemyPool::drawAll()
{
	for (const auto *entity : pool_)
	{
		if (entity->isActive_) entity->draw();
	}
}