#pragma once

#include <string>
#include <vector>

enum class GameMode;

class Lipsum
{
public:
	explicit Lipsum(GameMode mode);
	std::string next();

private:
	std::vector<std::string> words_;
};
