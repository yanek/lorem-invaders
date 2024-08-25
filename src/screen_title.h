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
	static constexpr float BANNER_STARTPOS = -150.0f;
	static constexpr float BANNER_ENDPOS = 32.0f;

	GameMode mode_{ GameMode::LOREM };
	int hiscore_;
	float bannerPosition_ = BANNER_STARTPOS;
	float animTime_ = 0.0f;
};