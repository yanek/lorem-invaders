#pragma once

#include "screen.h"

class TitleScreen final : public Screen
{
public:
	TitleScreen();
	void init() override;
	void update(float delta) override;
	void draw(float delta) override;
	void unload() override;
	const char *getName() const override { return "TitleScreen"; }

private:
	static constexpr int BANNER_STARTPOS = -150;
	static constexpr int BANNER_ENDPOS   = 32;

	GameMode mode_{ GameMode::LOREM };
	unsigned long hiscore_;
	int bannerPosition_{ BANNER_STARTPOS };
	float animTime_{ 0.0f };
};