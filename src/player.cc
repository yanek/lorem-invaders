#include "player.h"
#include "colors.h"
#include "resources.h"
#include "screens.h"
#include "viewport.h"
#include <algorithm>
#include <raylib.h>
#include <string>

void Player::Damage()
{
	this->hitpoints = std::max(this->hitpoints - 1, 0);
	if (this->IsDead())
	{
		screenManager.ChangeToScreen(new GameOverScreen{ this->score });
	}
}

bool Player::IsDead() const
{
	return this->hitpoints == 0;
}

void Player::DrawHud() const
{
	constexpr int size = 16;
	constexpr int radius = size / 2;
	constexpr int gap = 4;

	DrawRectangle(0, 0, Viewport::gameWidth, size + gap * 2, color::black);

	for (int i = 0; i < this->hitpoints; i++)
	{
		DrawCircle(gap + i * (size + gap) + radius, gap + radius, radius, color::red);
	}

	for (int i = 0; i < this->maxHitpoints; i++)
	{
		DrawCircleLines(gap + i * (size + gap) + radius, gap + radius, radius, color::white);
	}

	const int fntsize = res::font16.baseSize;
	const std::string score = TextFormat("%lu", this->score);
	const Vector2 scoreDimensions = MeasureTextEx(res::font16, score.c_str(), fntsize, 0);

	std::string scorePadding;
	for (int i = 0; i < 10 - score.length(); i++)
		scorePadding += "0";

	DrawTextEx(res::font16, scorePadding.c_str(), { Viewport::gameWidth - 90 - gap, gap + 2 }, size, 0, color::nearBlack);
	DrawTextEx(res::font16, score.c_str(), { Viewport::gameWidth - scoreDimensions.x - gap, gap + 2 }, size, 0, color::white);
	DrawTextEx(res::font16, "SCORE", { Viewport::gameWidth - gap - 140, gap + 2 }, size, 0, color::gray);
}

void Player::IncrementScore(const unsigned long value)
{
	this->score += value;
}
