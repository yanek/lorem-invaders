#pragma once
#include <raylib.h>

class Player
{
public:
	void Damage();
	bool IsDead() const;
	void DrawHud() const;
	void IncrementScore(unsigned long value);

private:
	unsigned long score{ 0 };
	unsigned char hitpoints{ 3 };
	unsigned char maxHitpoints{ 3 };
	Texture2D heartTexture{ LoadTexture("resources/heart.png") };
};
