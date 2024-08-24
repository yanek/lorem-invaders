#include "resources.h"

#include "utils.h"

Texture2D *Resources::textures_[(int)TextureId::NUM_TEXTURES] = { nullptr };
Sound *Resources::sounds_[(int)SoundId::NUM_SOUNDS] = { nullptr };
std::string *Resources::lipsum_[(int)GameMode::NUM_MODES] = { nullptr };
Font *Resources::font_ = nullptr;

void Resources::preload()
{
	font_ = new Font(LoadFont("resources/ibm-16.fnt"));
	textures_[(int)TextureId::HEART] = new Texture2D(LoadTexture("resources/heart.png"));
	textures_[(int)TextureId::BANNER] = new Texture2D(LoadTexture("resources/banner.png"));
	sounds_[(int)SoundId::CLICK] = new Sound(LoadSound("resources/click.wav"));
	sounds_[(int)SoundId::HIT] = new Sound(LoadSound("resources/hit.wav"));
	sounds_[(int)SoundId::HURT] = new Sound(LoadSound("resources/hurt.wav"));
	sounds_[(int)SoundId::PAUSE] = new Sound(LoadSound("resources/pause.wav"));
	sounds_[(int)SoundId::GAME_OVER] = new Sound(LoadSound("resources/gameover.wav"));
	TraceLog(LOG_INFO, "Finished preloading assets");
}

void Resources::unload()
{
	for (int i = 0; i < (int)SoundId::NUM_SOUNDS; i++)
	{
		if (sounds_[i] != nullptr)
		{
			UnloadSound(*sounds_[i]);
			delete sounds_[i];
			sounds_[i] = nullptr;
		}
	}

	for (int i = 0; i < (int)TextureId::NUM_TEXTURES; i++)
	{
		if (textures_[i] != nullptr)
		{
			UnloadTexture(*textures_[i]);
			delete textures_[i];
			textures_[i] = nullptr;
		}
	}

	for (int i = 0; i < (int)GameMode::NUM_MODES; i++)
	{
		if (lipsum_[i] != nullptr)
		{
			delete lipsum_[i];
			lipsum_[i] = nullptr;
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

const std::string *Resources::getLipsum(GameMode mode)
{
	if (lipsum_[(int)mode] == nullptr)
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
			E_BAIL(nullptr, "Dict not found for GameMode: %d", (int)mode);
		}

		lipsum_[(int)mode] = new std::string(LoadFileText(path));
	}

	return lipsum_[(int)mode];
}

const Sound *Resources::getSound(SoundId id)
{
	if (sounds_[(int)id] == nullptr)
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
			E_BAIL(nullptr, "Sound not found: %d", (int)id);
		}

		sounds_[(int)id] = new Sound(LoadSound(path));
	}

	return sounds_[(int)id];
}

const Texture2D *Resources::getTexture(TextureId id)
{
	if (textures_[(int)id] == nullptr)
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
			E_BAIL(nullptr, "Texture not found: %d", (int)id);
		}

		textures_[(int)id] = new Texture2D(LoadTexture(path));
	}

	return textures_[(int)id];
}