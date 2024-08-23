#pragma once

#include "screen.h"

class TitleScreen final : public Screen
{
public:
	TitleScreen();
	void init() override;
	void update() override;
	void draw() override;
	void unload() override;
	const char *getName() const override { return "title_screen"; }

private:
	GameMode mode_{ GameMode::LOREM };
	int hiscore_;
};