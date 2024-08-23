#include "lipsum.h"
#include "resources.h"
#include "screen.h"
#include "utils.h"

Lipsum::Lipsum(const GameMode mode)
{
	switch (mode)
	{
	case GameMode::LOREM:
		words_ = splitString(res::lipsum, "\n");
		break;
	case GameMode::ENGLISH:
		words_ = splitString(res::english, "\n");
		break;
	default:
		E_PANIC("Invalid game mode");
	}
}

std::string Lipsum::next()
{
	const size_t i = GetRandomValue(0, words_.size() - 1);
	return words_[i];
}