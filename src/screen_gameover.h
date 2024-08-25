#pragma once

#include "screen.h"

class GameOverScreen final : public Screen
{
public:
	explicit GameOverScreen(const unsigned long score) : score_{ score } {}
	void init() override;
	void update(float delta) override;
	void draw(float delta) override;
	void unload() override;
	const char *getName() const override { return "GameOverScreen"; }

private:
	unsigned long score_;
};
