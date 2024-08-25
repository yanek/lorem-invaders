#pragma once

#include "entity.h"
#include "event_bus.h"
#include "event_listener.h"
#include "fx_flash.h"
#include "fx_shake.h"
#include "screen.h"
#include "utils.h"

#include <raylib.h>

class InputBox final : public RenderedEntity, EventListener
{
public:
	explicit InputBox() { EVENT_SUBSCRIBE }
	~InputBox() override { EVENT_UNSUBSCRIBE }

	void update(f32 delta) override;
	void draw(f32 delta) const override;
	void clear();
	void notify(const Event &event) override;
	const char *getName() const override { return "InputBox"; }
	Rectangle getRect() const { return rect_; }
	void setRect(const Rectangle &rect) { rect_ = rect; }
	uint8_t getLayer() const override { return LAYER_GUI; }

private:
	static constexpr u8 MAX_INPUT_CHARS    = 31;
	static constexpr f32 CURSOR_BLINK_TIME = 0.5f;
	Rectangle rect_{};
	char value_[MAX_INPUT_CHARS + 1]{};
	u8 letterCount_         = 0;
	f32 cursorBlinkElapsed_ = 0.0f;
	Flash *flashPtr_{ nullptr };
	Shake *shakePtr_{ nullptr };
};