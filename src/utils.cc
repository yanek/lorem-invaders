#include "utils.h"
#include "colors.h"
#include "resources.h"
#include <raylib.h>
#include <string>

Font res_font16;

void DrawDebugData()
{
	const int val = std::max(1, std::min(GetFPS(), 999));
	const std::string fps = std::to_string(val);
	const auto fntsize = static_cast<float>(res_font16.baseSize);
	const auto vpwidth= static_cast<float>(GetScreenWidth());
	const float txtsize = MeasureTextEx(res_font16, fps.c_str(), fntsize, 0).x;

	const Vector2 pos{ vpwidth - txtsize - 1, 1 };
	const Rectangle rect{ pos.x - 1, pos.y, txtsize + 1, fntsize };

	DrawRectangleRec(rect, Fade(CLR_WHITE, 0.9f));
	DrawTextEx(res_font16, fps.c_str(), pos, fntsize, 0, CLR_BLACK);
}