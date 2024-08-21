#pragma once

#include "colors.h"

#include <raylib.h>
#include <string>

class InputBox
{
public:
	explicit InputBox(Rectangle rect);
	void Update(float delta);
	void Draw(int framecount) const;
	int GetMatch(const std::string &value) const;
	void Flash(Color color, int msduration);
	void Shake(float magnitude, int msduration);
	void Clear();

private:
	static constexpr int maxInputChars = 31;
	Rectangle rect;
	char value[maxInputChars + 1];
	int letterCount;
	float flashTimeout{ 0.0f };
	float flashElapsed{ 0.0f };
	Color flashColor{ color::transparent };
	float shakeTimeout{ 0.0f };
	float shakeElapsed{ 0.0f };
	float shakeMagnitude{ 0.0f };
	Vector2 shakeOffset{ 0.0f, 0.0f };
};