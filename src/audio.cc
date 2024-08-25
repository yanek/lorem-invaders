#include "audio.h"

#include <assert.h>

u8 Audio::head_ = 0;
u8 Audio::tail_ = 0;
PlaySoundMessage Audio::pending_[MAX_PENDING];

void Audio::init()
{
	InitAudioDevice();
	head_ = 0;
	tail_ = 0;
}

void Audio::close()
{
	CloseAudioDevice();
}

void Audio::play(const SoundId id)
{
	// Check if the sound is already pending
	// If it is, don't add it again
	for (u8 i = head_; i != tail_; i = (i + 1) % MAX_PENDING)
	{
		if (pending_[i].soundId == id) return;
	}

	assert((tail_ + 1) % MAX_PENDING != head_);
	pending_[tail_].soundId = id;
	tail_                   = (tail_ + 1) % MAX_PENDING;
}

void Audio::update()
{
	if (head_ == tail_) return;

	SoundId soundId    = pending_[head_].soundId;
	const Sound *sound = Resources::getSound(soundId);
	TraceLog(LOG_DEBUG, "Playing sound: %d (0x%X)", (i32)soundId, sound);
	PlaySound(*sound);

	head_ = (head_ + 1) % MAX_PENDING;
}
