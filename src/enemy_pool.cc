#include "enemy_pool.h"

#include "enemy.h"
#include "lipsum.h"
#include "resources.h"
#include "viewport.h"

void EnemyPool::init()
{
	for (Enemy * &i : pool_)
	{
		i = getScreen()->createEntity<Enemy>();
	}
}

void EnemyPool::spawn(Lipsum &lipsum) const
{
	i32 patternId      = GetRandomValue(0, (u8)EnemyPattern::NUM_PATTERNS - 1);
	const auto pattern = (EnemyPattern)patternId;
	const Font *font   = Resources::getFont();

	std::vector<SpawnData> spawnDatas;
	String value;
	i32 txtsize;

	switch (pattern)
	{
	case EnemyPattern::SLOW:
		value = lipsum.next();
		txtsize = (i32)MeasureTextEx(*font, value.c_str(), (f32)font->baseSize, 0).x;
		spawnDatas.emplace_back(
			SpawnData{
				Vector2{ (float)GetRandomValue(0, Viewport::GAME_WIDTH - txtsize), 0 }, // position
				Vector2{ 0, 60 },                                                       // velocity
				std::move(value)                                                        // value
			});
		break;
	case EnemyPattern::FAST:
		value = lipsum.next();
		txtsize = (i32)MeasureTextEx(*font, value.c_str(), (f32)font->baseSize, 0).x;
		spawnDatas.emplace_back(
			SpawnData{
				Vector2{ (float)GetRandomValue(0.0f, Viewport::GAME_WIDTH - txtsize), 0.0f }, // position
				Vector2{ 0.0f, 80.0f },                                                       // velocity
				std::move(value)                                                              // value
			});
		break;
	case EnemyPattern::FASTER:
		value = lipsum.next();
		txtsize = (i32)MeasureTextEx(*font, value.c_str(), (f32)font->baseSize, 0).x;
		spawnDatas.emplace_back(
			SpawnData{
				Vector2{ (float)GetRandomValue(0, Viewport::GAME_WIDTH - txtsize), 0 }, // position
				Vector2{ 0.0f, 100.0f },                                                // velocity
				std::move(value)                                                        // value
			});
		break;
	case EnemyPattern::BONUS:
		value = lipsum.next();
		spawnDatas.emplace_back(
			SpawnData{
				Vector2{ 0.0f, 64.0f }, // position
				Vector2{ 80.0f, 0.0f }, // velocity
				std::move(value)        // value
			});
		break;
	default:
		break;
	}

	for (SpawnData &data : spawnDatas)
	{
		i32 id = -1;

		// Find an inactive enemy in the pool
		for (u8 j = 0; j < MAX_POOLED; ++j)
		{
			if (!pool_[j]->isActive_)
			{
				id = j;
				break;
			}

			TraceLog(LOG_WARNING, "No pooled enemy available to spawn.");
		}

		// Skip if no inactive enemy was found
		if (id < 0) continue;

		Enemy *enemy     = pool_[id];
		enemy->id_       = id;
		enemy->position_ = data.position;
		enemy->velocity_ = data.velocity;
		enemy->value_    = std::move(data.value);
		enemy->isActive_ = true;
		enemy->pattern_  = pattern;

		TraceLog(LOG_DEBUG, "Creating enemy: '%s' (0x%X)", enemy->value_.c_str(), enemy);
	}
}

Enemy *EnemyPool::getEnemy(const i32 id) const
{
	return pool_[id];
}

void EnemyPool::update(const f32 delta)
{
	for (Enemy *entity : pool_)
	{
		if (entity == nullptr) continue;
		if (entity->isActive_) entity->update(delta);
	}
}