#pragma once

#include "entity.h"
#include "utils.h"

class Screen;
class GameScreen;
class Enemy;

enum class EnemyPattern : u8
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
	Enemy *spawn(const String &value) const;
	Enemy *getEnemy(i32 id) const;
	void update(f32 delta) override;
	const char *getName() const override { return "EnemyPool"; }

private:
	static constexpr u8 MAX_POOLED = 16;
	Enemy *pool_[MAX_POOLED]       = {};
};