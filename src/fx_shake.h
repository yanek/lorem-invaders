#pragma once

#include "fx_base.h"
#include <raylib.h>

class Shake final : public FxBase
{
public:
	Shake(f32 magnitude, i32 milliseconds);
	void update(f32 delta) override;
	Vector2 getOffset() const { return offset_; }

private:
	f32 magnitude_ = 0;
	Vector2 offset_;
};