#pragma once

#include "screen.h"
#include "utils.h"
#include <raylib.h>

enum class GameMode : unsigned char;

enum class SoundId : unsigned char
{
	CLICK = 0,
	HIT,
	HURT,
	HEAL,
	PAUSE,
	GAME_OVER,
	NUM_SOUNDS,
};

enum class TextureId : unsigned char
{
	HEART = 0,
	BANNER,
	NUM_TEXTURES,
};

class Resources
{
public:
	static void preload();
	static void unload();
	static const Font *getFont();
	static const String *getLipsum(GameMode mode);
	static const Sound *getSound(SoundId id);
	static const Texture2D *getTexture(TextureId id);

private:
	static Font *font_;
	static String *lipsum_[(unsigned char)GameMode::NUM_MODES];
	static Texture2D *textures_[(unsigned char)TextureId::NUM_TEXTURES];
	static Sound *sounds_[(unsigned char)SoundId::NUM_SOUNDS];
};