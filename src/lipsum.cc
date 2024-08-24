#include "lipsum.h"
#include "resources.h"
#include "screen.h"
#include "utils.h"

Lipsum::Lipsum(const GameMode mode)
{
	words_ = splitString(*Resources::getLipsum(mode), "\n");
}

std::string Lipsum::next()
{
	const size_t i = GetRandomValue(0, words_.size() - 1);
	return words_[i];
}