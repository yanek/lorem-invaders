#pragma once

#include "screen_game.h"
#include "utils.h"
#include <iostream>
#include <raylib.h>

class Enemy final
{
public:
	void Update(const GameScreen *screen, float delta);
	void Draw() const;
	void Despawn();

	Vector2 position = { 0, 0 };
	Vector2 velocity = { 0, 0 };
	bool active = false;

private:
	std::string value;
	size_t highlightOffset;
	size_t id = 0;
	friend class EnemyPool;
};

class EnemyPool final
{
public:
	size_t Spawn(const std::string &value);
	Enemy &Get(size_t id);
	size_t Count() const;
	void UpdateAll(const GameScreen *screen, float delta);
	void DrawAll() const;

private:
	std::vector<Enemy> pool;
};