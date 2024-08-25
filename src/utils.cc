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
	constexpr auto VIEWPORT_WIDTH = (f32)Viewport::WINDOW_WIDTH;

	const String fps  = TextFormat("%02iFPS", GetFPS());
	const Font *font  = Resources::getFont();
	const f32 fntsize = (f32)font->baseSize;
	const f32 txtsize = MeasureTextEx(*font, fps.c_str(), fntsize, 0).x;

	const Vector2 pos{ VIEWPORT_WIDTH / 2 - txtsize / 2, 1 };
	const Rectangle rect{ pos.x - 1, pos.y, txtsize + 1, fntsize };

	DrawRectangleRec(rect, Fade(color::primary, 0.9f));
	DrawTextEx(*font, fps.c_str(), pos, fntsize, 0, color::background);
}
