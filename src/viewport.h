#pragma once
#include <raylib.h>

class Viewport
{
public:
	Viewport();
	~Viewport();
	void InitRenderTexture();
	void BeginDrawing() const;
	void EndDrawing() const;
	void DrawRenderTexture() const;

	static constexpr int sGameWidth = 512;
	static constexpr int sGameHeight = 448;
	static constexpr int sWindowWidth = 1024;
	static constexpr int sWindowHeight = 896;

private:
	float mVirtualRatio = 0.0f;
	RenderTexture2D mRenderTex = {};
	Rectangle mSourceRec = {};
	Rectangle mDestRec = {};
};