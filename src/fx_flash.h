#pragma once

#include "fx_base.h"
#include <raylib.h>

class Flash final : public FxBase
{
public:
	Flash(Color color, int milliseconds);
	void Update(float delta) override;
	Color mColor;
};