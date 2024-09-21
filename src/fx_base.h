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
	float duration_ = 0;
	float elapsed_  = 0;
};