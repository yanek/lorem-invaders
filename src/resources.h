#pragma once

#include "screen.h"
#include <cstdint>
#include <raylib.h>
#include <string>

enum class GameMode;

enum class SoundId : uint8_t
{
	CLICK = 0,
	HIT,
	HURT,
	PAUSE,
	GAME_OVER,
	NUM_SOUNDS,
};

enum class TextureId : uint8_t
{
	HEART = 0,
	BANNER,
	NUM_TEXTURES,
};

class Resources
{
public:
	static void unloadResources();
	static const Font *getFont();
	static const std::string *getLipsum(GameMode mode);
	static const Sound *getSound(SoundId id);
	static const Texture2D *getTexture(TextureId id);

private:
	static Font *font_;
	static std::string *lipsum_[(int)GameMode::NUM_MODES];
	static Texture2D *textures_[(int)TextureId::NUM_TEXTURES];
	static Sound *sounds_[(int)SoundId::NUM_SOUNDS];
};