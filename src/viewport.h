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

	static constexpr int kGameWidth = 512;
	static constexpr int kGameHeight = 448;
	static constexpr int kWindowWidth = 1024;
	static constexpr int kWindowHeight = 896;

private:
	float mVirtualRatio = 0.0f;
	RenderTexture2D mRenderTex = {};
	Rectangle mSourceRec = {};
	Rectangle mDestRec = {};
};