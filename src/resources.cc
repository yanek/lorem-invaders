#include "resources.h"

#include "utils.h"

Font res::font16;
Texture2D res::textureHeart;
Texture2D res::textureBanner;
char *res::lipsum;
char *res::english;
Sound res::soundClick;
Sound res::soundHit;
Sound res::soundHurt;
Sound res::soundPause;
Sound res::soundGameOver;

void res::LoadResources()
{
	font16 = LoadFont("resources/ibm-16.fnt");
	textureHeart = LoadTexture("resources/heart.png");
	textureBanner = LoadTexture("resources/banner.png");
	lipsum = LoadFileText("resources/lorem.txt");
	english = LoadFileText("resources/words.txt");
	soundClick = LoadSound("resources/click.wav");
	soundHit = LoadSound("resources/hit.wav");
	soundHurt = LoadSound("resources/hurt.wav");
	soundPause = LoadSound("resources/pause.wav");
	soundGameOver = LoadSound("resources/gameover.wav");
}

void res::UnloadResources()
{
	UnloadFont(font16);
	UnloadFileText(lipsum);
	UnloadFileText(english);
	UnloadTexture(textureHeart);
	UnloadTexture(textureBanner);
	UnloadSound(soundClick);
	UnloadSound(soundHit);
	UnloadSound(soundHurt);
	UnloadSound(soundPause);
	UnloadSound(soundGameOver);
}

const Sound &res::GetSound(const SoundId id)
{
	switch (id)
	{
	case SoundId::CLICK:
		return soundClick;
	case SoundId::HIT:
		return soundHit;
	case SoundId::HURT:
		return soundHurt;
	case SoundId::PAUSE:
		return soundPause;
	case SoundId::GAME_OVER:
		return soundGameOver;
	default:
		E_PANIC("Invalid sound id");
	}
}