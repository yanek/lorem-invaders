#include "fx_shake.h"

Shake::Shake(const float magnitude, const int milliseconds)
	: FxBase(milliseconds), offset_({ 0, 0 }), magnitude_(magnitude)
{
}

void Shake::update(const float delta)
{
	elapsed_ += delta;
	const float mag = magnitude_;
	this->offset_ = Vector2{
		static_cast<float>(GetRandomValue(-mag, mag)),
		static_cast<float>(GetRandomValue(-mag, mag))
	};
}