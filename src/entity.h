#pragma once

#include <iostream>
#include <raylib.h>
#include <vector>

class Enemy
{
public:
	void Update();
	void Draw() const;

	Vector2 position = { 0, 0 };
	Vector2 velocity = { 0, 0 };
	bool active = false;

private:
	size_t id = -1;
	std::string value;
	friend class EnemyPool;
};

class EnemyPool
{
public:
	EnemyPool();
	size_t Spawn(const std::string &value);
	Enemy &Get(size_t id);
	void Despawn(size_t id);
	size_t Count() const;
	void UpdateAll();
	void DrawAll() const;

private:
	std::vector<Enemy> pool;
};