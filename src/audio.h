#pragma once
#include "resources.h"
#include "utils.h"

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
	static constexpr u8 MAX_PENDING = 16;
	static PlaySoundMessage pending_[MAX_PENDING];
	static u8 head_;
	static u8 tail_;
};
