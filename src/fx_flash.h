#pragma once

#include "fx_base.h"
#include <raylib.h>

class Flash final : public FxBase
{
public:
	Flash(Color color, i32 milliseconds);
	void update(f32 delta) override;
	Color color_;
};