#include "entity.h"
#include "resources.h"
#include <raylib.h>
#include <vector>

static std::vector<Enemy> entities;

void InitEnemies()
{
	entities = std::vector<Enemy>();
}

size_t CreateEnemy(char *value)
{
	size_t id = entities.size();

	TraceLog(LOG_INFO, "Creating Entity: %i", id);

	// Find inactive Entity.
	for (size_t i = 0; i < entities.size(); ++i)
	{
		const Enemy entity = entities[i];
		if (!entity.active)
		{
			id = i;
			break;
		}
	}

	if (id == entities.size())
	{
		entities.push_back(Enemy{ });
	}

	Enemy *entity = GetEnemy(id);

	*entity = Enemy{
		id,
		Vector2{ static_cast<float>(GetRandomValue(0, 512)), 0 },
		Vector2{ 0, 10 },
		value,
		true,
	};

	return id;
}

void DestroyEnemy(const size_t id)
{
	Enemy *entity = GetEnemy(id);
	entity->active = false;
}

Enemy *GetEnemy(const size_t id)
{
	return &entities[id];
}

size_t GetEnemyCount()
{
	return entities.size();
}

void UpdateEnemies()
{
	for (size_t i = 0; i < entities.size(); ++i)
	{
		Enemy *entity = GetEnemy(i);
		if (entity->active == 1)
		{
			entity->position.x += entity->velocity.x * GetFrameTime();
			entity->position.y += entity->velocity.y * GetFrameTime();
		}
	}
}

void DrawEnemies()
{
	for (size_t i = 0; i < entities.size(); ++i)
	{
		const Enemy *entity = GetEnemy(i);
		if (entity->active)
		{
			const auto fntsize = static_cast<float>(res_font16.baseSize);
			DrawTextEx(res_font16, entity->value, entity->position, fntsize, 0, WHITE);
		}
	}
}
