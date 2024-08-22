#pragma once
#include "resources.h"

struct EnemyKilledMessage
{
	unsigned int scoreValue;
	float verticalPostion;
};

struct PlayerDamagedMessage
{
};

struct PlaySoundMessage
{
	res::SoundId soundId;
};