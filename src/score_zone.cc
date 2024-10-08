//
// Created by ksian on 25/08/2024.
//

#include "score_zone.h"

#include "colors.h"
#include "viewport.h"
#include <raylib.h>

void ScoreZone::draw(float delta) const
{
	DrawRectangle(0, 0, Viewport::GAME_WIDTH, (float)height_, Fade(color::secondary, alpha_));
}