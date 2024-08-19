#pragma once

#include <raylib.h>
#include <stdio.h>

typedef struct
{
	size_t id;
	Vector2 position;
	Vector2 velocity;
	char *value;
	unsigned char isActive : 1;
} Enemy;

void InitEnemies(void);
size_t CreateEnemy(char *value);
void DestroyEnemy(size_t id);
Enemy *GetEnemy(size_t id);
size_t GetEnemyCount(void);
void UpdateEnemies(void);
void DrawEnemies(void);