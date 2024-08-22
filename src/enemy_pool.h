#pragma once

#include "enemy.h"

class EnemyPool final
{
public:
	size_t Spawn(const std::string &value);
	Enemy &Get(size_t id);
	size_t Count() const;
	void UpdateAll(const GameScreen *screen, float delta);
	void DrawAll() const;

private:
	std::vector<Enemy> mPool;
};