#pragma once

#include "screen.h"

class GameOverScreen final : public Screen
{
public:
	explicit GameOverScreen(const unsigned long score) : score_{ score } {}
	void init() override;
	void update() override;
	void draw() override;
	void unload() override;
	const char *getName() const override { return "gameover_screen"; }

private:
	unsigned long score_;
};
