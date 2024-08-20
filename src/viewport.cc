#include "viewport.h"
#include <raylib.h>
#include <utility>

Viewport::Viewport()
{
	InitWindow(windowWidth, windowHeight, "Lorem Invader");
}

Viewport::~Viewport()
{
	UnloadRenderTexture(this->rendertex);
	CloseWindow();
}

void Viewport::InitRenderTexture()
{
	this->rendertex = LoadRenderTexture(gameWidth, gameHeight);
	this->virtualRatio = static_cast<float>(windowWidth) / static_cast<float>(gameWidth);

	const float srcw = static_cast<float>(this->rendertex.texture.width);
	const float srch = static_cast<float>(-this->rendertex.texture.height);
	this->sourceRec = Rectangle{ 0.0f, 0.0f, srcw, srch };

	const float scale = std::min(GetScreenWidth() / gameWidth, GetScreenHeight() / gameHeight);
	const float dstw = static_cast<float>(gameWidth) * scale;
	const float dsth = static_cast<float>(gameHeight) * scale;

	this->destRec = Rectangle{
		(GetScreenWidth() - (static_cast<float>(gameWidth) * scale)) * 0.5f,
		(GetScreenHeight() - (static_cast<float>(gameHeight) * scale)) * 0.5f,
		dstw,
		dsth
	};
}

void Viewport::BeginDrawing() const
{
	BeginTextureMode(this->rendertex);
}

void Viewport::EndDrawing() const
{
	EndTextureMode();
}

void Viewport::DrawRenderTexture() const
{
	constexpr Vector2 origin{ 0.0f, 0.0f };
	DrawTexturePro(this->rendertex.texture, this->sourceRec, this->destRec, origin, 0.0f, WHITE);
}