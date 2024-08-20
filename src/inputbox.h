#pragma once

#include <raylib.h>
#include <string>

class InputBox
{
public:
	explicit InputBox(Rectangle rect);
	void Update();
	void Draw(int framecount) const;
	bool IsMatch(const std::string &value) const;
	void Clear();

private:
	Rectangle rect;
	std::string value;
	int letterCount;
};