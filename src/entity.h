#pragma once

#include <raylib.h>
#include <iostream>

typedef struct
{
	size_t id;
	Vector2 position;
	Vector2 velocity;
	char *value;
	bool active;
} Enemy;

void InitEnemies();
size_t CreateEnemy(char *value);
void DestroyEnemy(size_t id);
Enemy *GetEnemy(size_t id);
size_t GetEnemyCount();
void UpdateEnemies();
void DrawEnemies();