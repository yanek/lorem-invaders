#include "resources.h"

Font res::font16;
Texture2D res::textureHeart;
char *res::lipsum;
char *res::english;

void res::LoadResources()
{
	font16 = LoadFont("resources/ibm-16.fnt");
	textureHeart = LoadTexture("resources/heart.png");
	lipsum = LoadFileText("resources/lorem.txt");
	english = LoadFileText("resources/words.txt");
}

void res::UnloadResources()
{
	UnloadFont(font16);
	UnloadFileText(lipsum);
}