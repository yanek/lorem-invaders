#pragma once

#include "event_bus.h"
#include "event_listener.h"
#include "fx_flash.h"
#include "fx_shake.h"
#include "screen.h"
#include <raylib.h>
#include <string>

class InputBox final : EventListener
{
public:
	explicit InputBox(const Rectangle rect)
		: rect_(rect) { EVENT_SUBSCRIBE }
	~InputBox() override { EVENT_UNSUBSCRIBE }

	void update(float delta);
	void draw(float delta);
	void clear();
	void notify(const Event &event) override;

private:
	static constexpr int MAX_INPUT_CHARS = 31;
	static constexpr float CURSOR_BLINK_TIME = 0.5f;
	Rectangle rect_;
	char value_[MAX_INPUT_CHARS + 1]{};
	int letterCount_ = 0;
	float cursorBlinkElapsed_ = 0.0f;
	Flash *flashPtr_{ nullptr };
	Shake *shakePtr_{ nullptr };
};