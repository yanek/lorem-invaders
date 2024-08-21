#include "colors.h"
#include "resources.h"
#include "screens.h"
#include "viewport.h"

#include <raylib.h>

TitleScreen::TitleScreen()
	: Screen("title_screen")
{
}

void TitleScreen::Init()
{
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
	const auto fntsize = static_cast<float>(res::font16.baseSize);
	const auto msg1 = "Lorem Invader";
	const Vector2 textDimensions1 = MeasureTextEx(res::font16, msg1, fntsize * 2, 0);
	const float posX1 = Viewport::gameWidth / 2.0f - textDimensions1.x / 2.0f;
	DrawTextEx(res::font16, msg1, Vector2{ posX1, 72 }, fntsize * 2, 0, color::white);

	const auto msg2 = "Press [ENTER] to start";
	const Vector2 textDimensions2 = MeasureTextEx(res::font16, msg2, fntsize, 0);
	const float posX2 = Viewport::gameWidth / 2.0f - textDimensions2.x / 2.0f;
	DrawTextEx(res::font16, msg2, Vector2{ posX2, 128 }, fntsize, 0, color::gray);
}

void TitleScreen::Unload()
{
}