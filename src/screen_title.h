#pragma once

#include "screen.h"

class TitleScreen final : public Screen
{
public:
	TitleScreen();
	void init() override;
	void update(f32 delta) override;
	void draw(f32 delta) override;
	void unload() override;
	const char *getName() const override { return "TitleScreen"; }

private:
	static constexpr i32 BANNER_STARTPOS = -150.0f;
	static constexpr i32 BANNER_ENDPOS   = 32.0f;

	GameMode mode_{ GameMode::LOREM };
	u64 hiscore_;
	f32 bannerPosition_ = BANNER_STARTPOS;
	f32 animTime_       = 0.0f;
};