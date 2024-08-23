#include "inputbox.h"
#include "colors.h"
#include "fx_base.h"
#include "fx_flash.h"
#include "fx_shake.h"
#include "resources.h"
#include "viewport.h"
#include <raylib.h>

void InputBox::update(const float delta)
{
	int key = GetCharPressed();

	while (key > 0)
	{
		if ((key >= 32) && (key <= 125) && (letterCount_ < MAX_INPUT_CHARS))
		{
			value_[letterCount_] = static_cast<unsigned char>(key);
			value_[letterCount_ + 1] = '\0';
			letterCount_++;
		};

		key = GetCharPressed();
	}

	if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
	{
		letterCount_--;
		if (letterCount_ < 0)
			letterCount_ = 0;
		value_[letterCount_] = '\0';
	}

	if (IsKeyPressed(KEY_ENTER))
	{
		letterCount_ = 0;
		value_[0] = '\0';
	}

	if (flashPtr_ != nullptr)
	{
		flashPtr_->Update(delta);
		if (flashPtr_->ShouldDie())
		{
			delete flashPtr_;
			flashPtr_ = nullptr;
		}
	}

	if (shakePtr_ != nullptr)
	{
		shakePtr_->Update(delta);
		if (shakePtr_->ShouldDie())
		{
			delete shakePtr_;
			shakePtr_ = nullptr;
		}
	}
}

void InputBox::draw(const float delta)
{
	const auto fntsize = static_cast<float>(res::font16.baseSize);
	const float txtlen = MeasureTextEx(res::font16, value_, fntsize, 0).x;

	const Vector2 txtpos = {
		Viewport::kGameWidth / 2.0f - txtlen / 2.0f,
		rect_.y + 8.0f,
	};

	constexpr auto fgclr = color::primary;
	constexpr auto bgclr = color::black;

	Rectangle rect{
		rect_.x,
		rect_.y,
		rect_.width,
		rect_.height
	};

	if (shakePtr_ != nullptr)
	{
		rect.x += shakePtr_->mOffset.x;
		rect.y += shakePtr_->mOffset.y;
	};

	const Color flashColor =
		flashPtr_ != nullptr
			? flashPtr_->mColor
			: color::transparent;

	DrawRectangleRec(rect, bgclr);
	DrawRectangleLinesEx(rect, 2, fgclr);
	DrawTextEx(res::font16, value_, Vector2{ txtpos.x, txtpos.y }, fntsize, 0, fgclr);
	DrawRectangleRec(rect, flashColor);

	cursorBlinkElapsed_ += delta;
	if (cursorBlinkElapsed_ > CURSOR_BLINK_TIME && (letterCount_ < MAX_INPUT_CHARS))
	{
		const int x = (int)(txtpos.x + txtlen);
		const int y = (int)(txtpos.y);
		DrawText("|", x, y, res::font16.baseSize, fgclr);
	}

	if (cursorBlinkElapsed_ > CURSOR_BLINK_TIME * 2.0f)
	{
		cursorBlinkElapsed_ = 0.0f;
	}
}

int InputBox::getMatch(const std::string &value) const
{
	int matchCount = 0;
	for (size_t i = 0; i < value.length() && i < letterCount_; ++i)
	{
		if (value[i] == value_[i])
			matchCount++;
		else
			return 0;
	}

	return matchCount;
}

void InputBox::clear()
{
	value_[0] = '\0';
	letterCount_ = 0;
}

void InputBox::notify(const Event &event)
{
	TraceLog(LOG_DEBUG, "NOTIFY: %s", event.getName());
	if (event.getEventType() == EventType::PlayerHurt)
	{
		flashPtr_ = new Flash(color::accent, 30);
		shakePtr_ = new Shake(4.0f, 100);
	}
}