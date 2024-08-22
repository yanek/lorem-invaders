#pragma once

#include <string>
#include <vector>

enum class GameMode;

class Lipsum
{
public:
	explicit Lipsum(GameMode mode);
	std::string Next();

private:
	std::vector<std::string> mWords;
	int mCursor;
};
