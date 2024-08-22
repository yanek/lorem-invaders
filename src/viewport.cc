#include "viewport.h"

#include <algorithm>
#include <raylib.h>

Viewport::Viewport()
{
	InitWindow(kWindowWidth, kWindowHeight, "Lorem Invader");
}

Viewport::~Viewport()
{
	UnloadRenderTexture(mRenderTex);
	CloseWindow();
}

void Viewport::InitRenderTexture()
{
	mRenderTex = LoadRenderTexture(kGameWidth, kGameHeight);
	mVirtualRatio = static_cast<float>(kWindowWidth) / static_cast<float>(kGameWidth);

	const float srcw = static_cast<float>(mRenderTex.texture.width);
	const float srch = static_cast<float>(-mRenderTex.texture.height);
	mSourceRec = Rectangle{ 0.0f, 0.0f, srcw, srch };

	const float scale = std::min(GetScreenWidth() / kGameWidth, GetScreenHeight() / kGameHeight);
	const float dstw = static_cast<float>(kGameWidth) * scale;
	const float dsth = static_cast<float>(kGameHeight) * scale;

	this->mDestRec = Rectangle{
		(GetScreenWidth() - (static_cast<float>(kGameWidth) * scale)) * 0.5f,
		(GetScreenHeight() - (static_cast<float>(kGameHeight) * scale)) * 0.5f,
		dstw,
		dsth
	};
}

void Viewport::BeginDrawing() const
{
	BeginTextureMode(mRenderTex);
}

void Viewport::EndDrawing() const
{
	EndTextureMode();
}

void Viewport::DrawRenderTexture() const
{
	constexpr Vector2 origin{ 0.0f, 0.0f };
	DrawTexturePro(mRenderTex.texture, mSourceRec, mDestRec, origin, 0.0f, WHITE);
}