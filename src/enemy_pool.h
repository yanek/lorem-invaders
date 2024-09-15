#pragma once

#include "entity.h"
#include "utils.h"
#include <raylib.h>
#include <utility>

class Lipsum;
class Screen;
class GameScreen;
class Enemy;

enum class EnemyPattern : unsigned char
{
	SLOW = 0,
	FAST,
	FASTER,
	DOUBLE,
	TRIPLE,
	BONUS,
	NUM_PATTERNS
};

struct SpawnData final
{
	SpawnData(const Vector2 position, const Vector2 velocity, String value)
		: position(position), velocity(velocity), value(std::move(value)) {}

	Vector2 position;
	Vector2 velocity;
	String value;
};

class EnemyPool final : public Entity
{
public:
	void init();
	void spawn(Lipsum &lipsum) const;
	Enemy *getEnemy(int id) const;
	void update(float delta) override;
	const char *getName() const override { return "EnemyPool"; }

private:
	static constexpr unsigned char MAX_POOLED = 16;
	Enemy *pool_[MAX_POOLED]                  = {};
};
