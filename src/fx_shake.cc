#pragma once

#include "fx_shake.h"

Shake::Shake(const float magnitude, const int milliseconds)
	: FxBase(milliseconds), offset({ 0, 0 }), mMagnitude(magnitude)
{
}

void Shake::Update(const float delta)
{
	mElapsed += delta;
	const float mag = mMagnitude;
	this->offset = Vector2{
		static_cast<float>(GetRandomValue(-mag, mag)),
		static_cast<float>(GetRandomValue(-mag, mag))
	};
}