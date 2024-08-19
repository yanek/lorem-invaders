#include "resources.h"

void LoadResources(void)
{
	res_font16 = LoadFont("resources/ibm-16.fnt");
}

void UnloadResources(void)
{
	UnloadFont(res_font16);
}