#include "utils.h"
#include "colors.h"
#include <raylib.h>
#include <regex>
#include <string>

Font res_font16;

std::vector<std::string> SplitString(const std::string &str, const std::string &delim)
{
	// passing -1 as the submatch index parameter performs splitting
	std::regex re(delim);
	std::sregex_token_iterator
		first{ str.begin(), str.end(), re, -1 },
		last;
	return { first, last };
}

void DrawDebugData()
{
	const int val = std::max(1, std::min(GetFPS(), 999));
	const std::string fps = std::to_string(val);
	const auto fntsize = static_cast<float>(res_font16.baseSize);
	const auto vpwidth = static_cast<float>(GetScreenWidth());
	const float txtsize = MeasureTextEx(res_font16, fps.c_str(), fntsize, 0).x;

	const Vector2 pos{ vpwidth - txtsize - 1, 1 };
	const Rectangle rect{ pos.x - 1, pos.y, txtsize + 1, fntsize };

	DrawRectangleRec(rect, Fade(color::white, 0.9f));
	DrawTextEx(res_font16, fps.c_str(), pos, fntsize, 0, color::nearBlack);
}
