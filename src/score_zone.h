#pragma once

#include "entity.h"
#include "utils.h"
#include "viewport.h"

class ScoreZone final : public RenderedEntity
{
public:
	const char *getName() const override { return "ScoreZone"; }
	void draw(float delta) const override;
	u8 getLayer() const override { return LAYER_BACKGROUND; }
	void setHeight(const i16 height) { height_ = height; }
	void setAlpha(const f32 alpha) { alpha_ = alpha; }

	static constexpr u16 ZONE_2 = Viewport::GAME_HEIGHT / 3 + 32;
	static constexpr u16 ZONE_1 = ZONE_2 * 2 - 32;

private:
	u16 height_  = 0;
	float alpha_ = 1;
};
