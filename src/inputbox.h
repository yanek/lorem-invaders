#pragma once

#include <raylib.h>
#include <string>

class InputBox
{
public:
	explicit InputBox(Rectangle rect);
	void Update();
	void Draw(int framecount) const;
	int GetMatch(const std::string &value) const;
	void Clear();

private:
	static constexpr int maxInputChars = 31;
	Rectangle rect;
	char value[maxInputChars + 1];
	int letterCount;
};