#include "enemy_pool.h"

#include "enemy.h"
#include "lipsum.h"
#include "resources.h"
#include "viewport.h"

#include <queue>

static constexpr i32 COLUMN_COUNT = 5;
static constexpr f32 COLUMN_WIDTH = (f32)Viewport::GAME_WIDTH / COLUMN_COUNT;

static f32 getColumn(i32 columnIndex);
static f32 getRandomColumn();

void EnemyPool::init()
{
	for (Enemy * &i : pool_)
	{
		i = getScreen()->createEntity<Enemy>();
	}
}

void EnemyPool::spawn(Lipsum &lipsum) const
{
	std::queue<SpawnData> spawnDatas;
	i32 patternId      = GetRandomValue(0, (u8)EnemyPattern::NUM_PATTERNS - 1);
	const auto pattern = (EnemyPattern)patternId;

	switch (pattern)
	{
	case EnemyPattern::SLOW:
		spawnDatas.emplace(
			Vector2{ getRandomColumn(), 0 }, // position
			Vector2{ 0.0f, 40.0f },          // velocity
			lipsum.next()                    // value
			);
		break;
	case EnemyPattern::FAST:
		spawnDatas.emplace(
			Vector2{ getRandomColumn(), 0 }, // position
			Vector2{ 0.0f, 50.0f },          // velocity
			lipsum.next()                    // value
			);
		break;
	case EnemyPattern::FASTER:
		spawnDatas.emplace(
			Vector2{ getRandomColumn(), 0 }, // position
			Vector2{ 0.0f, 60.0f },          // velocity
			lipsum.next()                    // value
			);
		break;
	case EnemyPattern::DOUBLE:
		spawnDatas.emplace(
			Vector2{ getColumn(2), 0 }, // position
			Vector2{ 0.0f, 40.0f },     // velocity
			lipsum.next()               // value
			);
		spawnDatas.emplace(
			Vector2{ getColumn(4), 0 }, // position
			Vector2{ 0.0f, 40.0f },     // velocity
			lipsum.next()               // value
			);
		break;
	case EnemyPattern::TRIPLE:
		spawnDatas.emplace(
			Vector2{ getColumn(1), 0 }, // position
			Vector2{ 0.0f, 20.0f },     // velocity
			lipsum.next()               // value
			);
		spawnDatas.emplace(
			Vector2{ getColumn(3), 0 }, // position
			Vector2{ 0.0f, 20.0f },     // velocity
			lipsum.next()               // value
			);
		spawnDatas.emplace(
			Vector2{ getColumn(5), 0 }, // position
			Vector2{ 0.0f, 20.0f },     // velocity
			lipsum.next()               // value
			);
		break;
	case EnemyPattern::BONUS:
		spawnDatas.emplace(
			Vector2{ 0, 100 },      // position
			Vector2{ 80.0f, 0.0f }, // velocity
			lipsum.next()           // value
			);
		break;
	default:
		break;
	}

	while (!spawnDatas.empty())
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
		}

		// Skip if no inactive enemy was found
		if (id < 0)
		{
			TraceLog(LOG_WARNING, "No pooled enemy available to spawn.");
			spawnDatas.pop();
			continue;
		};

		const SpawnData &data = spawnDatas.front();
		Enemy *enemy          = pool_[id];
		enemy->id_            = id;
		enemy->position_      = data.position;
		enemy->velocity_      = data.velocity;
		enemy->value_         = data.value;
		enemy->isActive_      = true;
		enemy->pattern_       = pattern;
		spawnDatas.pop();

		TraceLog(LOG_DEBUG, "Creating enemy: '%s' {%d,%d} (0x%X)", enemy->value_.c_str(), enemy->position_.x, enemy->position_.y, enemy);
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

static f32 getColumn(const i32 columnIndex)
{
	const i32 idx = ((columnIndex - 1) % COLUMN_COUNT) + 1;
	return (COLUMN_WIDTH * (f32)idx) - (COLUMN_WIDTH / 2);
}

static f32 getRandomColumn()
{
	return getColumn(GetRandomValue(1, COLUMN_COUNT));
}