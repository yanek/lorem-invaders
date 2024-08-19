#include "colors.h"
#include "resources.h"
#include "screens.h"
#include <raylib.h>

void InitTitleScreen()
{
	TraceLog(LOG_INFO, "Title screen initialized");
}

void UpdateTitleScreen()
{
	if (IsKeyPressed(KEY_ENTER))
	{
		ChangeToScreen(SCR_GAME);
	}
}

void DrawTitleScreen()
{
	const float fontsize = (float)res_font16.baseSize;
	const char *msg1 = "Lorem Invader";
	const Vector2 textDimensions1 = MeasureTextEx(res_font16, msg1, fontsize * 2, 0);
	const float posX1 = 512.0f / 2.0f - textDimensions1.x / 2.0f;
	DrawTextEx(res_font16, msg1, Vector2{ posX1, 72 }, fontsize * 2, 0, CLR_WHITE);

	const char *msg2 = "Press [ENTER] to start";
	const Vector2 textDimensions2 = MeasureTextEx(res_font16, msg2, fontsize, 0);
	const float posX2 = 512.0f / 2.0f - textDimensions2.x / 2.0f;
	DrawTextEx(res_font16, msg2, Vector2{ posX2, 128 }, fontsize, 0, GRAY);
}

void UnloadTitleScreen()
{
	TraceLog(LOG_INFO, "Title screen unloaded");
}