#include "inputbox.h"

#include "colors.h"
#include "fx_base.h"
#include "fx_flash.h"
#include "fx_shake.h"
#include "resources.h"
#include "viewport.h"
#include <raylib.h>

void InputBox::update(const f32 delta)
{
	if (getScreen()->isPaused()) return;

	const EventBus *bus = ScreenManager::getEventBus();
	i32 key             = GetCharPressed();

	while (key > 0)
	{
		if ((key >= 32) && (key <= 125) && (letterCount_ < MAX_INPUT_CHARS))
		{
			value_[letterCount_]     = (unsigned char)key;
			value_[letterCount_ + 1] = '\0';
			letterCount_++;
			bus->fire(InputUpdatedEvent{ value_ });
		}

		key = GetCharPressed();
	}

	if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
	{
		letterCount_--;
		if (letterCount_ < 0)
			letterCount_ = 0;
		value_[letterCount_] = '\0';
		bus->fire(InputUpdatedEvent{ value_ });
	}

	if (IsKeyPressed(KEY_ENTER))
	{
		letterCount_ = 0;
		value_[0]    = '\0';
		bus->fire(InputUpdatedEvent{ value_ });
	}

	if (flashPtr_ != nullptr)
	{
		flashPtr_->update(delta);
		if (flashPtr_->shouldDie())
		{
			delete flashPtr_;
			flashPtr_ = nullptr;
		}
	}

	if (shakePtr_ != nullptr)
	{
		shakePtr_->update(delta);
		if (shakePtr_->shouldDie())
		{
			delete shakePtr_;
			shakePtr_ = nullptr;
		}
	}

	cursorBlinkElapsed_ += delta;
	if (cursorBlinkElapsed_ > CURSOR_BLINK_TIME * 2.0f)
	{
		cursorBlinkElapsed_ = 0.0f;
	}
}

void InputBox::draw(const f32 delta) const
{
	const Font *font   = Resources::getFont();
	const auto fntsize = (f32)font->baseSize;
	const f32 txtlen   = MeasureTextEx(*font, value_, fntsize, 0).x;

	const Vector2 txtpos = {
		Viewport::GAME_WIDTH / 2.0f - txtlen / 2.0f,
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
		rect.x += shakePtr_->getOffset().x;
		rect.y += shakePtr_->getOffset().y;
	}

	const Color flashColor =
		flashPtr_ != nullptr
			? flashPtr_->color_
			: color::transparent;

	DrawRectangleRec(rect, bgclr);
	DrawRectangleLinesEx(rect, 2, fgclr);
	DrawTextEx(*font, value_, Vector2{ txtpos.x, txtpos.y }, fntsize, 0, fgclr);
	DrawRectangleRec(rect, flashColor);

	if (cursorBlinkElapsed_ > CURSOR_BLINK_TIME && (letterCount_ < MAX_INPUT_CHARS))
	{
		const i32 x = (i32)(txtpos.x + txtlen);
		const i32 y = (i32)txtpos.y;
		DrawText("|", x, y, fntsize, fgclr);
	}
}

void InputBox::clear()
{
	value_[0]    = '\0';
	letterCount_ = 0;
}

void InputBox::notify(const Event &event)
{
	if (event.getEventType() == EventType::PlayerHurt)
	{
		flashPtr_ = new Flash(color::accent, 30);
		shakePtr_ = new Shake(4.0f, 100);
	}

	if (event.getEventType() == EventType::EnemyKilled)
	{
		clear();
	}
}