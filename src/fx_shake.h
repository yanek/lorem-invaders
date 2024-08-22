#pragma once

#include "fx_base.h"
#include <raylib.h>

class Shake final : public FxBase
{
public:
	Shake(float magnitude, int milliseconds);
	void Update(float delta) override;
	Vector2 mOffset;

private:
	float mMagnitude = 0;
};