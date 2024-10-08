#include "fx_base.h"

FxBase::FxBase(const int durationMilliseconds)
	: duration_((float)durationMilliseconds / 1000.0f)
{
}

bool FxBase::shouldDie() const
{
	return elapsed_ >= duration_;
}