#pragma once

#include <string>

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

class EnemyPool
{
public:
	static void init();
	static void close();
	static Enemy *spawn(const std::string &value);
	static Enemy *getEnemy(int id);
	static void updateAll(const GameScreen *screen, float delta);
	static void drawAll();

private:
	static constexpr int MAX_POOLED = 16;
	static Enemy *pool_[MAX_POOLED];
};