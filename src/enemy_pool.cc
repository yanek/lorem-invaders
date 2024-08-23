#include "enemy_pool.h"

#include "enemy.h"
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

	assert(id != -1);
	TraceLog(LOG_DEBUG, "Creating enemy: %i", id);

	int patternId = GetRandomValue(0, (int)EnemyPattern::NUM_PATTERNS - 1);
	const auto pattern = (EnemyPattern)patternId;

	const float txtsize = MeasureTextEx(res::font16, value.c_str(), res::font16.baseSize, 0).x;
	float posx = 0.0f;
	float posy = 0.0f;

	Vector2 velocity = {};
	switch (pattern)
	{
	case EnemyPattern::SLOW:
		// Randomize horizontal position while making sure that the text does not overflow the viewport.
		posx = GetRandomValue(0, Viewport::GAME_WIDTH - txtsize);
		velocity = Vector2{ 0, 80 };
		break;
	case EnemyPattern::FAST:
		// Randomize horizontal position while making sure that the text does not overflow the viewport.
		posx = GetRandomValue(0, Viewport::GAME_WIDTH - txtsize);
		velocity = Vector2{ 0, 100 };
		break;
	case EnemyPattern::FASTER:
		posx = GetRandomValue(0, Viewport::GAME_WIDTH - txtsize);
		velocity = Vector2{ 0, 120 };
		break;
	case EnemyPattern::DIAGONAL_LEFT:
		posx = Viewport::GAME_WIDTH - txtsize;
		velocity = Vector2{ -40, 100 };
		break;
	case EnemyPattern::DIAGONAL_RIGHT:
		posx = 0.0f;
		velocity = Vector2{ 40, 100 };
		break;
	case EnemyPattern::BONUS:
		posx = 0.0f;
		velocity = Vector2{ 50, 0 };
	default:
		velocity = Vector2{ 0, 50 };
	}

	Enemy *enemy = pool_[id];
	enemy->id_ = id;
	enemy->position_ = Vector2{ posx, posy };
	enemy->velocity_ = velocity;
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