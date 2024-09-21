#include "fx_shake.h"

Shake::Shake(const int magnitude, const int milliseconds)
	: FxBase(milliseconds), magnitude_(magnitude), offset_({ 0, 0 })
{
}

void Shake::update(const float delta)
{
	elapsed_ += delta;
	const int mag = magnitude_;
	this->offset_ = Vector2{
		(float)GetRandomValue(-mag, mag),
		(float)GetRandomValue(-mag, mag)
	};
}