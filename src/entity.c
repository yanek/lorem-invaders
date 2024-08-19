#include "entity.h"
#include "arraylist.h"
#include "utils.h"
#include <raylib.h>
#include <stdlib.h>

#define MSG_COULD_NOT_APPEND_ENTITY "Could not append entity to list"

static ArrayList *entityList;

void InitEntities(void)
{
	entityList = CreateArrayList(sizeof(Entity), 0);
}

size_t CreateEntity()
{
	size_t id = entityList->len;

	// Find inactive Entity.
	for (size_t i = 0; i < entityList->len; ++i)
	{
		const Entity *entity = GetArrayListItem(entityList, i);
		if (!entity->isActive)
		{
			id = i;
			break;
		}
	}

	if (id == entityList->len)
	{
		if (AddArrayListItem(entityList, &(Entity){ 0 }) == (size_t)-1)
		{
			E_PANIC(MSG_COULD_NOT_APPEND_ENTITY);
		}
	}

	Entity *entity = GetEntity(id);

	*entity = (Entity){
		.isActive = true,
	};

	return id;
}

void DestroyEntity(const size_t id)
{
	Entity *entity = GetEntity(id);
	entity->isActive = false;
}

Entity *GetEntity(const size_t id)
{
	return GetArrayListItem(entityList, id);
}

size_t GetEntityCount(void)
{
	return entityList->len;
}
