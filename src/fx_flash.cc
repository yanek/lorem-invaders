//
// Created by ksian on 21/08/2024.
//

#include "fx_flash.h"

Flash::Flash(const Color color, const i32 milliseconds)
	: FxBase(milliseconds), color_(color)
{
}

void Flash::update(const f32 delta)
{
	elapsed_ += delta;
}
