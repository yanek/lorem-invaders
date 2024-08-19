#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef struct
{
	size_t id;
	bool isActive;
} Entity;

void InitEntities(void);
size_t CreateEntity();
void DestroyEntity(size_t id);
Entity *GetEntity(size_t id);
size_t GetEntityCount(void);
