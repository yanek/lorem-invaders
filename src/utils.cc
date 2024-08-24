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
	const std::regex re(delim);
	std::sregex_token_iterator
		first{ str.begin(), str.end(), re, -1 },
		last;
	return { first, last };
}

void drawDebugData()
{
	const std::string fps = TextFormat("%02iFPS", GetFPS());
	const Font* font = Resources::getFont();
	const auto fntsize = (float)font->baseSize;
	constexpr auto vpwidth = (float)Viewport::WINDOW_WIDTH;
	const float txtsize = MeasureTextEx(*font, fps.c_str(), fntsize, 0).x;

	const Vector2 pos{ vpwidth / 2 - txtsize / 2, 1 };
	const Rectangle rect{ pos.x - 1, pos.y, txtsize + 1, fntsize };

	DrawRectangleRec(rect, Fade(color::primary, 0.9f));
	DrawTextEx(*font, fps.c_str(), pos, fntsize, 0, color::background);
}
