#include "player.h"

#include "viewport.h"

#include <algorithm>
#include <raylib.h>

void Player::Damage()
{
	this->hitpoints = std::max(this->hitpoints - 1, 0);
}

bool Player::IsDead() const
{
	return this->hitpoints == 0;
}

void Player::DrawHud() const
{
	constexpr int size = 16;
	constexpr int gap = 4;

	DrawRectangle(0, 0, Viewport::gameWidth, size + gap * 2, BLACK);

	for (int i = 0; i < this->hitpoints; i++)
	{
		DrawRectangle(gap + i * (size + gap), gap, size, size, RED);
	}

	for (int i = 0; i < this->maxHitpoints; i++)
	{
		DrawRectangleLines(gap + i * (size + gap), gap, size, size, WHITE);
	}
}
