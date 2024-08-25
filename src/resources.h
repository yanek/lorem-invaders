#pragma once

#include "screen.h"
#include "utils.h"
#include <raylib.h>

enum class GameMode : u8;

enum class SoundId : u8
{
	CLICK = 0,
	HIT,
	HURT,
	PAUSE,
	GAME_OVER,
	NUM_SOUNDS,
};

enum class TextureId : u8
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
	static String *lipsum_[(u8)GameMode::NUM_MODES];
	static Texture2D *textures_[(u8)TextureId::NUM_TEXTURES];
	static Sound *sounds_[(u8)SoundId::NUM_SOUNDS];
};