#include "fx_base.h"

FxBase::FxBase(const i32 durationMilliseconds)
	: duration_((f32)durationMilliseconds / 1000.0f)
{
}

bool FxBase::shouldDie() const
{
	return elapsed_ >= duration_;
}