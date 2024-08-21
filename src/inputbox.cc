#include "inputbox.h"

#include "colors.h"
#include "resources.h"
#include "viewport.h"
#include <raylib.h>

InputBox::InputBox(const Rectangle rect)
	: rect(rect), value{}, letterCount(0)
{
}

void InputBox::Update()
{
	int key = GetCharPressed();

	while (key > 0)
	{
		if ((key >= 32) && (key <= 125) && (this->letterCount < maxInputChars))
		{
			this->value[this->letterCount] = static_cast<unsigned char>(key);
			this->value[this->letterCount + 1] = '\0';
			this->letterCount++;
		};

		key = GetCharPressed();
	}

	if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
	{
		this->letterCount--;
		if (this->letterCount < 0)
			this->letterCount = 0;
		this->value[this->letterCount] = '\0';
	}

	if (IsKeyPressed(KEY_ENTER))
	{
		this->letterCount = 0;
		this->value[0] = '\0';
	}
}

void InputBox::Draw(const int framecount) const
{
	const auto fntsize = static_cast<float>(res::font16.baseSize);
	const float txtlen = MeasureTextEx(res::font16, this->value, fntsize, 0).x;

	const Vector2 txtpos = {
		Viewport::gameWidth / 2.0f - txtlen / 2.0f,
		this->rect.y + 8.0f,
	};

	constexpr auto fgclr = color::white;
	constexpr auto bgclr = color::black;

	DrawRectangleRec(this->rect, bgclr);
	DrawRectangleLinesEx(this->rect, 2, fgclr);
	DrawTextEx(res::font16, this->value, Vector2{ txtpos.x, txtpos.y }, fntsize, 0, fgclr);

	if ((framecount / 20 % 2 == 0) && (this->letterCount < maxInputChars))
	{
		const int x = static_cast<int>(txtpos.x + txtlen);
		const int y = static_cast<int>(txtpos.y);
		DrawText("|", x, y, res::font16.baseSize, fgclr);
	}
}

int InputBox::GetMatch(const std::string &value) const
{
	int matchCount = 0;
	for (size_t i = 0; i < value.length() && i < this->letterCount; ++i)
	{
		if (value[i] == this->value[i])
		{
			matchCount++;
		}
		else
		{
			return 0;
		}
	}

	return matchCount;
}

void InputBox::Clear()
{
	this->value[0] = '\0';
	this->letterCount = 0;
}