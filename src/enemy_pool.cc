#include "enemy_pool.h"

#include "enemy.h"
#include "resources.h"
#include "viewport.h"
#include <cassert>

void EnemyPool::init()
{
	for (Enemy * &i : pool_)
	{
		i = getScreen()->createEntity<Enemy>();
	}
}

Enemy *EnemyPool::spawn(const String &value) const
{
	i32 id = -1;

	// Find inactive enemy.
	for (i32 i = 0; i < MAX_POOLED; ++i)
	{
		if (!pool_[i]->isActive_)
		{
			id = i;
			break;
		}
	}

	assert(id != -1);

	i32 patternId      = GetRandomValue(0, (u8)EnemyPattern::NUM_PATTERNS - 1);
	const auto pattern = (EnemyPattern)patternId;

	const Font *font  = Resources::getFont();
	const i32 txtsize = (i32)MeasureTextEx(*font, value.c_str(), (f32)font->baseSize, 0).x;
	i32 posx          = 0;
	i32 posy          = 0;

	Vector2 velocity;
	switch (pattern)
	{
	case EnemyPattern::SLOW:
		// Randomize horizontal position while making sure that the text does not overflow the viewport.
		posx = GetRandomValue(0, Viewport::GAME_WIDTH - txtsize);
		velocity = Vector2{ 0, 60 };
		break;
	case EnemyPattern::FAST:
		// Randomize horizontal position while making sure that the text does not overflow the viewport.
		posx = GetRandomValue(0, Viewport::GAME_WIDTH - txtsize);
		velocity = Vector2{ 0, 80 };
		break;
	case EnemyPattern::FASTER:
		posx = GetRandomValue(0, Viewport::GAME_WIDTH - txtsize);
		velocity = Vector2{ 0, 100 };
		break;
	case EnemyPattern::BONUS:
		posy = 64;
		posx     = 0;
		velocity = Vector2{ 100, 0 };
		break;
	default:
		velocity = Vector2{ 0, 60 };
	}

	Enemy *enemy     = pool_[id];
	enemy->id_       = id;
	enemy->position_ = Vector2{ (f32)posx, (f32)posy };
	enemy->velocity_ = velocity;
	enemy->value_    = value;
	enemy->isActive_ = true;
	enemy->pattern_  = pattern;

	TraceLog(LOG_DEBUG, "Creating enemy: '%s' (0x%X)", value.c_str(), enemy);

	return enemy;
}

Enemy *EnemyPool::getEnemy(const i32 id) const
{
	return pool_[id];
}

void EnemyPool::update(const f32 delta)
{
	for (auto *entity : pool_)
	{
		if (entity == nullptr) continue;
		if (entity->isActive_) entity->update(delta);
	}
}