#pragma once

#include "utils.h"

class FxBase
{
public:
	virtual ~FxBase()                = default;
	virtual void update(f32 delta) = 0;
	bool shouldDie() const;

protected:
	explicit FxBase(i32 durationMilliseconds);
	f32 duration_ = 0;
	f32 elapsed_  = 0;
};