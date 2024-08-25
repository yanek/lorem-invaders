#pragma once
#include "utils.h"

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

	static constexpr i16 GAME_WIDTH    = 512;
	static constexpr i16 GAME_HEIGHT   = 448;
	static constexpr i16 WINDOW_WIDTH  = 1024;
	static constexpr i16 WINDOW_HEIGHT = 896;

private:
	f32 virtualRatio_              = 0.0f;
	RenderTexture2D renderTexture_ = {};
	Rectangle sourceRect           = {};
	Rectangle destRect             = {};
};