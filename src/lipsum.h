#pragma once

#include "utils.h"
#include <string>
#include <vector>

enum class GameMode : u8;

class Lipsum
{
public:
	explicit Lipsum(GameMode mode);
	String next();

private:
	std::vector<String> words_;
};
