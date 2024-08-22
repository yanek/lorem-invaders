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
	void Draw(int framecount) const;
	int GetMatch(const std::string &value) const;
	void Clear();

private:
	static constexpr int kMaxInputChars = 31;
	Rectangle mRect;
	char mValue[kMaxInputChars + 1];
	int mLetterCount;
};