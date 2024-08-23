#pragma once

#include "fx_flash.h"
#include "fx_shake.h"
#include <raylib.h>
#include <string>

class InputBox
{
public:
	Flash *mFlash{ nullptr };
	Shake *mShake{ nullptr };
	explicit InputBox(Rectangle rect);
	void Update(float delta);
	void Draw(float delta);
	int GetMatch(const std::string &value) const;
	void Clear();

private:
	static constexpr int kMaxInputChars = 31;
	static constexpr float CURSOR_BLINK_TIME = 0.5f;
	Rectangle mRect;
	char mValue[kMaxInputChars + 1];
	int mLetterCount;
	float cursorBlinkElapsed_ = 0.0f;
};