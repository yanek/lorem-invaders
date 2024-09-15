#pragma once

#include "fx_base.h"
#include <raylib.h>

class Shake final : public FxBase
{
public:
	Shake(int magnitude, int milliseconds);
	void update(float delta) override;
	Vector2 getOffset() const { return offset_; }

private:
	int magnitude_ = 0;
	Vector2 offset_;
};