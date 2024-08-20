#pragma once

#include <string>
#include <vector>

class Lipsum {
public:
	Lipsum();
	std::string Next();
private:
	std::vector<std::string> words;
	int cursor;
};

