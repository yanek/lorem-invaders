#include "inputbox.h"
#include "colors.h"
#include "fx_base.h"
#include "fx_flash.h"
#include "fx_shake.h"
#include "resources.h"
#include "viewport.h"
#include <raylib.h>

InputBox::InputBox(const Rectangle rect)
	: mRect(rect), mValue{}, mLetterCount(0)
{
}

void InputBox::Update(const float delta)
{
	int key = GetCharPressed();

	while (key > 0)
	{
		if ((key >= 32) && (key <= 125) && (mLetterCount < kMaxInputChars))
		{
			mValue[mLetterCount] = static_cast<unsigned char>(key);
			mValue[mLetterCount + 1] = '\0';
			mLetterCount++;
		};

		key = GetCharPressed();
	}

	if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
	{
		mLetterCount--;
		if (mLetterCount < 0)
			mLetterCount = 0;
		mValue[mLetterCount] = '\0';
	}

	if (IsKeyPressed(KEY_ENTER))
	{
		mLetterCount = 0;
		mValue[0] = '\0';
	}

	if (mFlash != nullptr)
	{
		mFlash->Update(delta);
		if (mFlash->ShouldDie())
		{
			delete mFlash;
			mFlash = nullptr;
		}
	}

	if (mShake != nullptr)
	{
		mShake->Update(delta);
		if (mShake->ShouldDie())
		{
			delete mShake;
			mShake = nullptr;
		}
	}
}

void InputBox::Draw(const int framecount) const
{
	const auto fntsize = static_cast<float>(res::font16.baseSize);
	const float txtlen = MeasureTextEx(res::font16, mValue, fntsize, 0).x;

	const Vector2 txtpos = {
		Viewport::kGameWidth / 2.0f - txtlen / 2.0f,
		mRect.y + 8.0f,
	};

	constexpr auto fgclr = color::primary;
	constexpr auto bgclr = color::black;

	Rectangle rect{
		mRect.x,
		mRect.y,
		mRect.width,
		mRect.height
	};

	if (mShake != nullptr)
	{
		rect.x += mShake->mOffset.x;
		rect.y += mShake->mOffset.y;
	};

	const Color flashColor =
		mFlash != nullptr
			? mFlash->mColor
			: color::transparent;

	DrawRectangleRec(rect, bgclr);
	DrawRectangleLinesEx(rect, 2, fgclr);
	DrawTextEx(res::font16, mValue, Vector2{ txtpos.x, txtpos.y }, fntsize, 0, fgclr);
	DrawRectangleRec(rect, flashColor);

	if ((framecount / 20 % 2 == 0) && (mLetterCount < kMaxInputChars))
	{
		const int x = static_cast<int>(txtpos.x + txtlen);
		const int y = static_cast<int>(txtpos.y);
		DrawText("|", x, y, res::font16.baseSize, fgclr);
	}
}

int InputBox::GetMatch(const std::string &value) const
{
	int matchCount = 0;
	for (size_t i = 0; i < value.length() && i < mLetterCount; ++i)
	{
		if (value[i] == mValue[i])
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
	mValue[0] = '\0';
	mLetterCount = 0;
}