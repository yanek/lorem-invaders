#pragma once

#include <raylib.h>

namespace res
{
	enum class SoundId : unsigned char;
	extern Font font16;
	extern Texture2D textureHeart;
	extern Texture2D textureBanner;
	extern char *lipsum;
	extern char *english;
	extern Sound soundClick;
	extern Sound soundHit;
	extern Sound soundHurt;
	extern Sound soundPause;
	extern Sound soundGameOver;

	void LoadResources();
	void UnloadResources();
	const Sound &GetSound(SoundId id);

	enum class SoundId : unsigned char
	{
		CLICK = 0,
		HIT,
		HURT,
		PAUSE,
		GAME_OVER,
	};
}
