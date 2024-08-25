#pragma once

#include "screen.h"

class GameOverScreen final : public Screen
{
public:
	explicit GameOverScreen(const u64 score)
		: score_{ score } {}

	void init() override;
	void update(f32 delta) override;
	void draw(f32 delta) override;
	void unload() override;
	const char *getName() const override { return "GameOverScreen"; }

private:
	u64 score_;
};
