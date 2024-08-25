#pragma once

#include "entity.h"
#include <string>

class Screen;
class GameScreen;
class Enemy;

enum class EnemyPattern : int
{
	SLOW = 0,
	FAST,
	FASTER,
	DIAGONAL_LEFT,
	DIAGONAL_RIGHT,
	BONUS,
	NUM_PATTERNS
};

class EnemyPool final : public Entity
{
public:
	void init();
	Enemy *spawn(const std::string &value) const;
	Enemy *getEnemy(int id) const;
	void update(float delta) override;
	const char *getName() const override { return "EnemyPool"; }

private:
	static constexpr int MAX_POOLED = 16;
	Enemy *pool_[MAX_POOLED]        = {};
};