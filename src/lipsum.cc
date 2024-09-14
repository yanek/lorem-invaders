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
	const usize i = GetRandomValue(0, (i32)words_.size() - 1);
	return words_[i];
}