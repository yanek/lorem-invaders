#include "entity.h"
#include "arraylist.h"
#include "resources.h"
#include "utils.h"
#include <raylib.h>
#include <stdlib.h>

#define MSG_COULD_NOT_APPEND_ENTITY "Could not append entity to list"

static ArrayList *_entities;
Font res_font16;

void InitEnemies(void)
{
	_entities = CreateArrayList(sizeof(Enemy), 0);
}

size_t CreateEnemy(char *value)
{
	size_t id = _entities->len;

	TraceLog(LOG_INFO, "Creating Entity: %i", id);

	// Find inactive Entity.
	for (size_t i = 0; i < _entities->len; ++i)
	{
		const Enemy *entity = GetArrayListItem(_entities, i);
		if (!entity->isActive)
		{
			id = i;
			break;
		}
	}

	if (id == _entities->len)
	{
		if (AddArrayListItem(_entities, &(Enemy){ 0 }) == (size_t)-1)
		{
			E_PANIC(MSG_COULD_NOT_APPEND_ENTITY);
		}
	}

	Enemy *entity = GetEnemy(id);

	*entity = (Enemy){
		.isActive = 1,
		.value = value,
		.position = (Vector2){
		  .x = GetRandomValue(0, 512),
		  .y = 0 },
		.velocity = (Vector2){ .x = 0, .y = 10 }
	};

	return id;
}

void DestroyEnemy(const size_t id)
{
	Enemy *entity = GetEnemy(id);
	entity->isActive = false;
}

Enemy *GetEnemy(const size_t id)
{
	return GetArrayListItem(_entities, id);
}

size_t GetEnemyCount(void)
{
	return _entities->len;
}

void UpdateEnemies(void)
{
	for (size_t i = 0; i < _entities->len; ++i)
	{
		Enemy *entity = GetArrayListItem(_entities, i);
		if (entity->isActive == 1)
		{
			entity->position.x += entity->velocity.x * GetFrameTime();
			entity->position.y += entity->velocity.y * GetFrameTime();
		}
	}
}

void DrawEnemies(void)
{
	for (size_t i = 0; i < _entities->len; ++i)
	{
		const Enemy *entity = GetArrayListItem(_entities, i);
		if (entity->isActive)
		{
			DrawTextEx(res_font16, entity->value, entity->position, res_font16.baseSize, 0, WHITE);
		}
	}
}
