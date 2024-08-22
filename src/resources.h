#pragma once

#include <raylib.h>

namespace res
{
	extern Font font16;
	extern Texture2D textureHeart;
	extern char *lipsum;
	extern char *english;

	void LoadResources();
	void UnloadResources();
}
