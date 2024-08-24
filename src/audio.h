#pragma once
#include "resources.h"

struct PlaySoundMessage
{
	SoundId soundId;
};

class Audio
{
public:
	static void init();
	static void close();
	static void play(SoundId id);
	static void update();

private:
	static constexpr int MAX_PENDING = 16;
	static PlaySoundMessage pending_[MAX_PENDING];
	static int head_;
	static int tail_;
};
