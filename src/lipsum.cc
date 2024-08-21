#include "lipsum.h"
#include "resources.h"
#include "utils.h"

Lipsum::Lipsum()
{
	this->words = SplitString(res::lipsum, "\n");
	this->cursor = 0;
}

std::string Lipsum::Next()
{
	const size_t i = GetRandomValue(0, this->words.size() - 1);
	return this->words[i];
}