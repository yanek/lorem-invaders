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

	static constexpr int gameWidth = 512;
	static constexpr int gameHeight = 448;
	static constexpr int windowWidth = 1024;
	static constexpr int windowHeight = 896;

private:
	float virtualRatio = 0.0f;
	RenderTexture2D rendertex = {};
	Rectangle sourceRec = {};
	Rectangle destRec = {};
};