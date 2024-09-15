#pragma once

#include "fx_base.h"
#include <raylib.h>

class Flash final : public FxBase
{
public:
	Flash(Color color, int milliseconds);
	void update(float delta) override;
	Color color_;
};