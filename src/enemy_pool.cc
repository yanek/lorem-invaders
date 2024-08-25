#include "enemy_pool.h"

#include "enemy.h"
#include "resources.h"
#include "viewport.h"
#include <cassert>

void EnemyPool::init()
{
	for (int i = 0; i < MAX_POOLED; ++i)
	{
		pool_[i] = getScreen()->createEntity<Enemy>();
	}
}

Enemy *EnemyPool::spawn(const std::string &value) const
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

	int patternId      = GetRandomValue(0, (int)EnemyPattern::NUM_PATTERNS - 1);
	const auto pattern = (EnemyPattern)patternId;

	const Font *font    = Resources::getFont();
	const float txtsize = MeasureTextEx(*font, value.c_str(), font->baseSize, 0).x;
	float posx          = 0.0f;
	float posy          = 0.0f;

	Vector2 velocity = {};
	switch (pattern)
	{
	case EnemyPattern::SLOW:
		// Randomize horizontal position while making sure that the text does not overflow the viewport.
		posx     = GetRandomValue(0, Viewport::GAME_WIDTH - txtsize);
		velocity = Vector2{ 0, 80 };
		break;
	case EnemyPattern::FAST:
		// Randomize horizontal position while making sure that the text does not overflow the viewport.
		posx     = GetRandomValue(0, Viewport::GAME_WIDTH - txtsize);
		velocity = Vector2{ 0, 100 };
		break;
	case EnemyPattern::FASTER:
		posx     = GetRandomValue(0, Viewport::GAME_WIDTH - txtsize);
		velocity = Vector2{ 0, 120 };
		break;
	case EnemyPattern::DIAGONAL_LEFT:
		posx     = Viewport::GAME_WIDTH - txtsize;
		velocity = Vector2{ -80, 100 };
		break;
	case EnemyPattern::DIAGONAL_RIGHT:
		posx     = 0.0f;
		velocity = Vector2{ 80, 100 };
		break;
	case EnemyPattern::BONUS:
		posx     = 0.0f;
		posy     = 64.0f;
		velocity = Vector2{ 160, 0 };
		break;
	default:
		velocity = Vector2{ 0, 50 };
	}

	Enemy *enemy     = pool_[id];
	enemy->id_       = id;
	enemy->position_ = Vector2{ posx, posy };
	enemy->velocity_ = velocity;
	enemy->value_    = value;
	enemy->isActive_ = true;
	enemy->pattern_  = pattern;

	TraceLog(LOG_DEBUG, "Creating enemy: '%s' (0x%X)", value.c_str(), enemy);

	return enemy;
}

Enemy *EnemyPool::getEnemy(const int id) const
{
	return pool_[id];
}

void EnemyPool::update(const float delta)
{
	for (auto *entity : pool_)
	{
		if (entity == nullptr) continue;
		if (entity->isActive_) entity->update(delta);
	}
}