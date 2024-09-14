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
	static constexpr i32 BANNER_STARTPOS = -150;
	static constexpr i32 BANNER_ENDPOS   = 32;

	GameMode mode_{ GameMode::LOREM };
	u64 hiscore_;
	i32 bannerPosition_ = BANNER_STARTPOS;
	f32 animTime_       = 0.0f;
};