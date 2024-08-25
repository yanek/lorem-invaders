#pragma once

#include "utils.h"

class FxBase
{
public:
	virtual ~FxBase()                = default;
	virtual void update(float delta) = 0;
	bool shouldDie() const;

protected:
	explicit FxBase(int durationMilliseconds);
	f32 duration_ = 0;
	f32 elapsed_  = 0;
};