#include "utils.h"
#include "colors.h"
#include "resources.h"
#include "viewport.h"

#include <raylib.h>
#include <regex>
#include <string>

std::vector<std::string> splitString(const std::string &str, const std::string &delim)
{
	// passing -1 as the submatch index parameter performs splitting
	std::regex re(delim);
	std::sregex_token_iterator
		first{ str.begin(), str.end(), re, -1 },
		last;
	return { first, last };
}

void drawDebugData()
{
	const std::string fps = TextFormat("%02iFPS", GetFPS());
	const auto fntsize = static_cast<float>(res::font16.baseSize);
	constexpr auto vpwidth = static_cast<float>(Viewport::kWindowWidth);
	const float txtsize = MeasureTextEx(res::font16, fps.c_str(), fntsize, 0).x;

	const Vector2 pos{ vpwidth / 2 - txtsize / 2, 1 };
	const Rectangle rect{ pos.x - 1, pos.y, txtsize + 1, fntsize };

	DrawRectangleRec(rect, Fade(color::primary, 0.9f));
	DrawTextEx(res::font16, fps.c_str(), pos, fntsize, 0, color::background);
}
