#pragma once

#include "entity.h"
#include "event_bus.h"
#include "event_listener.h"
#include "fx_flash.h"
#include "fx_shake.h"
#include "screen.h"
#include <raylib.h>

class InputBox final : public RenderedEntity, EventListener
{
public:
	explicit InputBox() { EVENT_SUBSCRIBE }
	~InputBox() override { EVENT_UNSUBSCRIBE }

	void update(float delta) override;
	void draw(float delta) const override;
	void clear();
	void notify(const Event &event) override;
	const char *getName() const override { return "InputBox"; }
	Rectangle getRect() const { return rect_; }
	void setRect(const Rectangle &rect) { rect_ = rect; }
	uint8_t getLayer() const override { return 100; }

private:
	static constexpr int MAX_INPUT_CHARS     = 31;
	static constexpr float CURSOR_BLINK_TIME = 0.5f;
	Rectangle rect_{};
	char value_[MAX_INPUT_CHARS + 1]{};
	int letterCount_          = 0;
	float cursorBlinkElapsed_ = 0.0f;
	Flash *flashPtr_{ nullptr };
	Shake *shakePtr_{ nullptr };
};