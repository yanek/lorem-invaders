#include "fx_shake.h"

Shake::Shake(const f32 magnitude, const i32 milliseconds)
	: FxBase(milliseconds), magnitude_(magnitude), offset_({ 0, 0 })
{
}

void Shake::update(const f32 delta)
{
	elapsed_ += delta;
	const f32 mag = magnitude_;
	this->offset_ = Vector2{
		(f32)GetRandomValue(-mag, mag),
		(f32)GetRandomValue(-mag, mag)
	};
}