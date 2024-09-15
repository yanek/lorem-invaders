#pragma once

#include <raylib.h>

class Viewport
{
public:
	Viewport();
	~Viewport();
	void initRenderTexture();
	void beginDrawing() const;
	void endDrawing() const;
	void drawRenderTexture() const;

	static constexpr int GAME_WIDTH    = 512;
	static constexpr int GAME_HEIGHT   = 448;
	static constexpr int WINDOW_WIDTH  = 1024;
	static constexpr int WINDOW_HEIGHT = 896;

private:
	float virtualRatio_{ 0.0f };
	RenderTexture2D renderTexture_{};
	Rectangle sourceRect{};
	Rectangle destRect{};
};