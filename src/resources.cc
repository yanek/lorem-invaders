#include "resources.h"

Font res::font16;
char* res::lipsum;

void res::LoadResources()
{
	font16 = LoadFont("resources/ibm-16.fnt");
	lipsum = LoadFileText("resources/lorem.txt");
}

void res::UnloadResources()
{
	UnloadFont(font16);
	UnloadFileText(lipsum);
}