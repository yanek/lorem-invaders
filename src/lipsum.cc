#include "lipsum.h"
#include "resources.h"
#include "screen.h"
#include "utils.h"

Lipsum::Lipsum(const GameMode mode)
{
	switch (mode)
	{
	case GameMode::LOREM:
		mWords = SplitString(res::lipsum, "\n");
		break;
	case GameMode::ENGLISH:
		mWords = SplitString(res::english, "\n");
		break;
	default:
		E_PANIC("Invalid game mode");
	}
	mCursor = 0;
}

std::string Lipsum::Next()
{
	const size_t i = GetRandomValue(0, mWords.size() - 1);
	return mWords[i];
}