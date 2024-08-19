#include "resources.h"

void LoadResources()
{
	res_font16 = LoadFont("resources/ibm-16.fnt");
}

void UnloadResources()
{
	UnloadFont(res_font16);
}