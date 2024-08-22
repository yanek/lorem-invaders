#include "fx_base.h"

FxBase::FxBase(const int durationMilliseconds)
	: mDuration(durationMilliseconds / 1000.0f)
{
}

bool FxBase::ShouldDie() const
{
	return mElapsed >= mDuration;
}