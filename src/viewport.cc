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
	virtualRatio_ = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(GAME_WIDTH);

	const float srcw = static_cast<float>(renderTexture_.texture.width);
	const float srch = static_cast<float>(-renderTexture_.texture.height);
	sourceRect = Rectangle{ 0.0f, 0.0f, srcw, srch };

	const float scale = std::min(GetScreenWidth() / GAME_WIDTH, GetScreenHeight() / GAME_HEIGHT);
	const float dstw = static_cast<float>(GAME_WIDTH) * scale;
	const float dsth = static_cast<float>(GAME_HEIGHT) * scale;

	this->destRect = Rectangle{
		(GetScreenWidth() - (static_cast<float>(GAME_WIDTH) * scale)) * 0.5f,
		(GetScreenHeight() - (static_cast<float>(GAME_HEIGHT) * scale)) * 0.5f,
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
	constexpr Vector2 origin{ 0.0f, 0.0f };
	DrawTexturePro(renderTexture_.texture, sourceRect, destRect, origin, 0.0f, WHITE);
}