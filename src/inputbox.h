#pragma once

#include <raylib.h>
#include <string>

class InputBox
{
public:
	explicit InputBox(Rectangle rect);
	void Update();
	void Draw(int framecount) const;

private:
	Rectangle rect;
	std::string value;
	int letterCount;
};