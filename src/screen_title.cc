#include "colors.h"
#include "resources.h"
#include "screens.h"
#include <raylib.h>

void TitleScreen::Init()
{
	TraceLog(LOG_INFO, "Title screen initialized");
}

void TitleScreen::Update()
{
	if (IsKeyPressed(KEY_ENTER))
	{
		screenManager.ChangeToScreen(new GameScreen{});
	}
}

void TitleScreen::Draw()
{
	const auto fntsize = static_cast<float>(res_font16.baseSize);
	const auto msg1 = "Lorem Invader";
	const Vector2 textDimensions1 = MeasureTextEx(res_font16, msg1, fntsize * 2, 0);
	const float posX1 = 512.0f / 2.0f - textDimensions1.x / 2.0f;
	DrawTextEx(res_font16, msg1, Vector2{ posX1, 72 }, fntsize * 2, 0, CLR_WHITE);

	const auto msg2 = "Press [ENTER] to start";
	const Vector2 textDimensions2 = MeasureTextEx(res_font16, msg2, fntsize, 0);
	const float posX2 = 512.0f / 2.0f - textDimensions2.x / 2.0f;
	DrawTextEx(res_font16, msg2, Vector2{ posX2, 128 }, fntsize, 0, GRAY);
}

void TitleScreen::Unload()
{
	TraceLog(LOG_INFO, "Title screen unloaded");
}