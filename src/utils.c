#include <raylib.h>
#include <stdio.h>
#include "screens.h"
#include "utils.h"

#include "colors.h"

#include <math.h>
#include <stdlib.h>

char *IntegerToText(const int val)
{
	const size_t len = floor(log10(abs(val))) + 2;
	char *buffer = malloc(len);
#ifdef __EMSCRIPTEN__
	sprintf(buffer, "%d", val);
#else
	sprintf_s(buffer, len, "%d", val);
#endif
	return buffer;
}

void DrawDebugData(void)
{
	const int val = MAX(1, MIN(GetFPS(), 999));
	char *fps = IntegerToText(val);
	const int txtsize = MeasureTextEx(font, fps, font.baseSize, 0).x;

	const Vector2 pos = (Vector2){
		.x = GetScreenWidth() - txtsize - 1,
		.y = 1
	};

	DrawRectangle(pos.x - 1, pos.y,  txtsize + 1, font.baseSize, Fade(CLR_WHITE, 0.9f));
	DrawTextEx(font, fps, pos, font.baseSize, 0, CLR_BLACK);

	free(fps);
}