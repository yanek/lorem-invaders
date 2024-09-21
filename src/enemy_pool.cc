#include "enemy_pool.h"

#include "enemy.h"
#include "lipsum.h"
#include "screen_game.h"
#include "viewport.h"
#include <queue>

static constexpr int COLUMN_COUNT   = 5;
static constexpr float COLUMN_WIDTH = (float)Viewport::GAME_WIDTH / COLUMN_COUNT;

static float getColumn(int columnIndex);
static float getRandomColumn();
static EnemyPattern pickRandomPattern(float difficulty);

static const WeightedPattern patterns[]{
	WeightedPattern(EnemyPattern::SLOW, 100, 1.0f),
	WeightedPattern(EnemyPattern::FAST, 40, 2.0f),
	WeightedPattern(EnemyPattern::FASTER, 20, 1.5f),
	WeightedPattern(EnemyPattern::DOUBLE, 10, 1.5f),
	WeightedPattern(EnemyPattern::TRIPLE, 5, 1.2f),
	WeightedPattern(EnemyPattern::BONUS, 1, 0.8f)
};

void EnemyPool::init()
{
	for (Enemy *&i : pool_)
	{
		i = getScreen()->createEntity<Enemy>();
	}
}

void EnemyPool::spawn(Lipsum &lipsum) const
{
	std::queue<SpawnData> spawnDatas;

	const auto screen          = (GameScreen *)getScreen();
	const float difficulty     = screen->getDifficultyModifier();
	const EnemyPattern pattern = pickRandomPattern(difficulty);

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
		int id = -1;

		// Find an inactive enemy in the pool
		for (unsigned char j = 0; j < MAX_POOLED; ++j)
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

Enemy *EnemyPool::getEnemy(const int id) const
{
	return pool_[id];
}

void EnemyPool::update(const float delta)
{
	for (Enemy *entity : pool_)
	{
		if (entity == nullptr) continue;
		if (entity->isActive_) entity->update(delta);
	}
}

static float getColumn(const int columnIndex)
{
	const int idx = ((columnIndex - 1) % COLUMN_COUNT) + 1;
	return (COLUMN_WIDTH * (float)idx) - (COLUMN_WIDTH / 2);
}

static float getRandomColumn()
{
	return getColumn(GetRandomValue(1, COLUMN_COUNT));
}

static EnemyPattern pickRandomPattern(const float difficulty)
{
	int totalWeight = 0;

	for (const WeightedPattern pattern : patterns)
	{
		totalWeight += (int)((float)pattern.weight * ((difficulty -1.0f) * pattern.difficultyMultiplier + 1.0f));
	}

	int randomNum = GetRandomValue(1, totalWeight) - 1;
	for (const WeightedPattern pattern : patterns)
	{
		randomNum -= (int)((float)pattern.weight * ((difficulty -1.0f) * pattern.difficultyMultiplier + 1.0f));
		if (randomNum < 0)
		{
			TraceLog(LOG_TRACE, "Picked pattern: %d", pattern.pattern);
			return pattern.pattern;
		}
	}

	TraceLog(LOG_ERROR, "Failed to pick a pattern.");
	return EnemyPattern::INVALID;
}