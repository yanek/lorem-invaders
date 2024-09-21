#include "viewport.h"

#include <algorithm>
#include <raylib.h>

Viewport::Viewport()
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Lorem Invader");
}

Viewport::~Viewport()
{
	UnloadRenderTexture(renderTexture_);
	CloseWindow();
}

void Viewport::initRenderTexture()
{
	renderTexture_ = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
	virtualRatio_  = (float)WINDOW_WIDTH / (float)GAME_WIDTH;

	const auto srcw = (float)renderTexture_.texture.width;
	const auto srch = (float)-renderTexture_.texture.height;
	sourceRect       = Rectangle{ 0.0f, 0.0f, srcw, srch };

	const float scale = std::min((float)GetScreenWidth() / GAME_WIDTH, (float)GetScreenHeight() / GAME_HEIGHT);
	const float dstw  = static_cast<float>(GAME_WIDTH) * scale;
	const float dsth  = static_cast<float>(GAME_HEIGHT) * scale;

	this->destRect = Rectangle{
		((float)GetScreenWidth() - ((float)GAME_WIDTH * scale)) * 0.5f,
		((float)GetScreenHeight() - ((float)GAME_HEIGHT * scale)) * 0.5f,
		dstw,
		dsth
	};
}

void Viewport::beginDrawing() const
{
	BeginTextureMode(renderTexture_);
}

void Viewport::endDrawing() const
{
	EndTextureMode();
}

void Viewport::drawRenderTexture() const
{
	constexpr Vector2 ORIGIN{ 0.0f, 0.0f };
	DrawTexturePro(renderTexture_.texture, sourceRect, destRect, ORIGIN, 0.0f, WHITE);
}