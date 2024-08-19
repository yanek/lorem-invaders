#include "colors.h"
#include "resources.h"
#include "screens.h"
#include <raylib.h>

Font res_font16;

void InitTitleScreen(void)
{
	TraceLog(LOG_INFO, "Title screen initialized");
}

void UpdateTitleScreen(void)
{
	if (IsKeyPressed(KEY_ENTER))
	{
		ChangeToScreen(SCR_GAME);
	}
}

void DrawTitleScreen(void)
{
	const char *msg1 = "Lorem Invader";
	const Vector2 textDimensions1 = MeasureTextEx(res_font16, msg1, res_font16.baseSize * 2, 0);
	const int posX1 = 512 / 2 - textDimensions1.x / 2;
	DrawTextEx(res_font16, msg1, (Vector2){ posX1, 72 }, res_font16.baseSize * 2, 0, CLR_WHITE);

	const char *msg2 = "Press [ENTER] to start";
	const Vector2 textDimensions2 = MeasureTextEx(res_font16, msg2, res_font16.baseSize, 0);
	const int posX2 = 512 / 2 - textDimensions2.x / 2;
	DrawTextEx(res_font16, msg2, (Vector2){ posX2, 128 }, res_font16.baseSize, 0, GRAY);
}

void UnloadTitleScreen(void)
{
	TraceLog(LOG_INFO, "Title screen unloaded");
}