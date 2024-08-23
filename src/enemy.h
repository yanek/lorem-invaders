#pragma once

#include "screen_game.h"
#include <iostream>
#include <raylib.h>

class Shake;

class Enemy final
{
public:
	void Update(const GameScreen *screen, float delta);
	void Draw() const;
	void Despawn();

	Vector2 mPosition = { 0, 0 };
	Vector2 mVelocity = { 0, 0 };
	bool mActive = false;

private:
	size_t mId = 0;
	std::string mValue;
	size_t mHighlightOffset;
	unsigned char mAlpha = 255;
	bool mIsDying = false;
	Shake *mShake;
	friend class EnemyPool;
};
