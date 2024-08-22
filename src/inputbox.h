#pragma once

#include "fx_flash.h"
#include "fx_shake.h"
#include <raylib.h>
#include <string>

class InputBox
{
public:
	Flash *flash{ nullptr };
	Shake *shake{ nullptr };
	explicit InputBox(Rectangle rect);
	void Update(float delta);
	void Draw(int framecount) const;
	int GetMatch(const std::string &value) const;
	void Clear();

private:
	static constexpr int maxInputChars = 31;
	Rectangle rect;
	char value[maxInputChars + 1];
	int letterCount;
};