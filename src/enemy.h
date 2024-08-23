#pragma once

#include "enemy_pool.h"
#include "screen_game.h"
#include <iostream>
#include <raylib.h>

enum class EnemyPattern;
class Shake;

class Enemy final
{
	friend class EnemyPool;

public:
	void update(const GameScreen *screen, float delta);
	void draw() const;
	void despawn();

private:
	size_t id_ = 0;
	Vector2 position_ = { 0, 0 };
	Vector2 velocity_ = { 0, 0 };
	std::string value_;
	size_t highlightOffset_;
	bool isActive_ = false;
	bool isDying_ = false;
	EnemyPattern pattern_ = (EnemyPattern)0;
	Shake *shake_;
};
