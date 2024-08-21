#pragma once

#include <raylib.h>

namespace res
{
	extern Font font16;
	extern char *lipsum;
	extern char *english;

	void LoadResources();
	void UnloadResources();
}
