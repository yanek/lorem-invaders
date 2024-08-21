#include "lipsum.h"
#include "resources.h"
#include "screens.h"
#include "utils.h"

Lipsum::Lipsum(GameMode mode)
{
	switch (mode)
	{
	case GameMode::LOREM:
		this->words = SplitString(res::lipsum, "\n");
		break;
	case GameMode::ENGLISH:
		this->words = SplitString(res::english, "\n");
		break;
	default:
		E_PANIC("Invalid game mode");
	}
	this->cursor = 0;
}

std::string Lipsum::Next()
{
	const size_t i = GetRandomValue(0, this->words.size() - 1);
	return this->words[i];
}