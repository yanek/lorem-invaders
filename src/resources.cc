#include "resources.h"

#include "utils.h"

Texture2D *Resources::textures_[(unsigned char)TextureId::NUM_TEXTURES] = { nullptr };
Sound *Resources::sounds_[(unsigned char)SoundId::NUM_SOUNDS]           = { nullptr };
std::string *Resources::lipsum_[(unsigned char)GameMode::NUM_MODES]     = { nullptr };
Font *Resources::font_                                        = nullptr;

void Resources::preload()
{
	font_                            = new Font(LoadFont("resources/ibm-16.fnt"));
	textures_[(unsigned char)TextureId::HEART]  = new Texture2D(LoadTexture("resources/heart.png"));
	textures_[(unsigned char)TextureId::BANNER] = new Texture2D(LoadTexture("resources/banner.png"));
	sounds_[(unsigned char)SoundId::CLICK]      = new Sound(LoadSound("resources/click.wav"));
	sounds_[(unsigned char)SoundId::HIT]        = new Sound(LoadSound("resources/hit.wav"));
	sounds_[(unsigned char)SoundId::HURT]       = new Sound(LoadSound("resources/hurt.wav"));
	sounds_[(unsigned char)SoundId::PAUSE]      = new Sound(LoadSound("resources/pause.wav"));
	sounds_[(unsigned char)SoundId::GAME_OVER]  = new Sound(LoadSound("resources/gameover.wav"));
	TraceLog(LOG_INFO, "Finished preloading assets");
}

void Resources::unload()
{
	for (Sound * &sound : sounds_)
	{
		if (sound != nullptr)
		{
			UnloadSound(*sound);
			delete sound;
			sound = nullptr;
		}
	}

	for (Texture2D * &texture : textures_)
	{
		if (texture != nullptr)
		{
			UnloadTexture(*texture);
			delete texture;
			texture = nullptr;
		}
	}

	for (String * &lispsum : lipsum_)
	{
		if (lispsum != nullptr)
		{
			delete lispsum;
			lispsum = nullptr;
		}
	}

	if (font_ != nullptr)
	{
		UnloadFont(*font_);
		delete font_;
		font_ = nullptr;
	}
}

const Font *Resources::getFont()
{
	if (font_ == nullptr)
		font_ = new Font(LoadFont("resources/ibm-16.fnt"));

	return font_;
}

const String *Resources::getLipsum(GameMode mode)
{
	if (lipsum_[(unsigned char)mode] == nullptr)
	{
		const char *path;
		switch (mode)
		{
		case GameMode::ENGLISH:
			path = "resources/words.txt";
			break;
		case GameMode::LOREM:
			path = "resources/lorem.txt";
			break;
		default:
			E_BAIL(nullptr, "Dict not found for GameMode: %d", (unsigned char)mode);
		}

		lipsum_[(unsigned char)mode] = new std::string(LoadFileText(path));
	}

	return lipsum_[(unsigned char)mode];
}

const Sound *Resources::getSound(SoundId id)
{
	if (sounds_[(unsigned char)id] == nullptr)
	{
		const char *path;
		switch (id)
		{
		case SoundId::CLICK:
			path = "resources/click.wav";
			break;
		case SoundId::HIT:
			path = "resources/hit.wav";
			break;
		case SoundId::HURT:
			path = "resources/hurt.wav";
			break;
		case SoundId::PAUSE:
			path = "resources/pause.wav";
			break;
		case SoundId::GAME_OVER:
			path = "resources/gameover.wav";
			break;
		default:
			E_BAIL(nullptr, "Sound not found: %d", (unsigned char)id);
		}

		sounds_[(unsigned char)id] = new Sound(LoadSound(path));
	}

	return sounds_[(unsigned char)id];
}

const Texture2D *Resources::getTexture(TextureId id)
{
	if (textures_[(unsigned char)id] == nullptr)
	{
		const char *path;
		switch (id)
		{
		case TextureId::HEART:
			path = "resources/heart.png";
			break;
		case TextureId::BANNER:
			path = "resources/banner.png";
			break;
		default:
			E_BAIL(nullptr, "Texture not found: %d", (unsigned char)id);
		}

		textures_[(unsigned char)id] = new Texture2D(LoadTexture(path));
	}

	return textures_[(unsigned char)id];
}