#include "viewport.h"

#include <algorithm>
#include <raylib.h>

Viewport::Viewport()
{
	InitWindow(sWindowWidth, sWindowHeight, "Lorem Invader");
}

Viewport::~Viewport()
{
	UnloadRenderTexture(mRenderTex);
	CloseWindow();
}

void Viewport::InitRenderTexture()
{
	mRenderTex = LoadRenderTexture(sGameWidth, sGameHeight);
	mVirtualRatio = static_cast<float>(sWindowWidth) / static_cast<float>(sGameWidth);

	const float srcw = static_cast<float>(mRenderTex.texture.width);
	const float srch = static_cast<float>(-mRenderTex.texture.height);
	mSourceRec = Rectangle{ 0.0f, 0.0f, srcw, srch };

	const float scale = std::min(GetScreenWidth() / sGameWidth, GetScreenHeight() / sGameHeight);
	const float dstw = static_cast<float>(sGameWidth) * scale;
	const float dsth = static_cast<float>(sGameHeight) * scale;

	this->mDestRec = Rectangle{
		(GetScreenWidth() - (static_cast<float>(sGameWidth) * scale)) * 0.5f,
		(GetScreenHeight() - (static_cast<float>(sGameHeight) * scale)) * 0.5f,
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