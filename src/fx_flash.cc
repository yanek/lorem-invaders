//
// Created by ksian on 21/08/2024.
//

#include "fx_flash.h"

Flash::Flash(const Color color, const int milliseconds)
	: FxBase(milliseconds), mColor(color)
{
}

void Flash::Update(const float delta)
{
	mElapsed += delta;
}
