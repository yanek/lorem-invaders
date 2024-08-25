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
	virtualRatio_  = (f32)WINDOW_WIDTH / (f32)GAME_WIDTH;

	const float srcw = (f32)renderTexture_.texture.width;
	const float srch = (f32)-renderTexture_.texture.height;
	sourceRect       = Rectangle{ 0.0f, 0.0f, srcw, srch };

	const float scale = std::min(GetScreenWidth() / GAME_WIDTH, GetScreenHeight() / GAME_HEIGHT);
	const float dstw  = static_cast<float>(GAME_WIDTH) * scale;
	const float dsth  = static_cast<float>(GAME_HEIGHT) * scale;

	this->destRect = Rectangle{
		(GetScreenWidth() - ((f32)GAME_WIDTH * scale)) * 0.5f,
		(GetScreenHeight() - ((f32)GAME_HEIGHT * scale)) * 0.5f,
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