#pragma once

#include "entity.h"
#include "viewport.h"

class ScoreZone final : public RenderedEntity
{
public:
	const char *getName() const override { return "ScoreZone"; }
	void draw(float delta) const override;
	unsigned char getLayer() const override { return LAYER_BACKGROUND; }
	void setHeight(const int height) { height_ = height; }
	void setAlpha(const float alpha) { alpha_ = alpha; }

	static constexpr unsigned int ZONE_2 = Viewport::GAME_HEIGHT / 3 + 32;
	static constexpr unsigned int ZONE_1 = ZONE_2 * 2 - 32;

private:
	unsigned int height_ = 0;
	float alpha_         = 1.0f;
};
