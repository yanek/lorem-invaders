#include "colors.h"
#include "resources.h"
#include "screens.h"
#include "utils.h"
#include <raylib.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

constexpr int virtualScreenWidth = 512;
constexpr int virtualScreenHeight = 448;
constexpr int screenWidth = 1024;
constexpr int screenHeight = 768;
float virtualRatio = 0.0f;
RenderTexture2D target = {};
Rectangle sourceRec = {};
Rectangle destRec = {};

void UpdateDrawFrame();

int main()
{
	SetTraceLogLevel(LOG_TRACE);
	TraceLog(LOG_TRACE, "Starting game");
	InitWindow(screenWidth, screenHeight, "Lorem Invader");
	LoadResources();

	target = LoadRenderTexture(virtualScreenWidth, virtualScreenHeight);
	virtualRatio = static_cast<float>(screenWidth) / static_cast<float>(virtualScreenWidth);
	sourceRec = Rectangle{ 0.0f, 0.0f, static_cast<float>(target.texture.width), static_cast<float>(-target.texture.height) };
	destRec = Rectangle{ -virtualRatio, -virtualRatio, static_cast<float>(screenWidth) + virtualRatio * 2.0f, static_cast<float>(screenHeight) + virtualRatio * 2.0f };

	SetTextLineSpacing(16);

	screenManager.ChangeToScreen(new TitleScreen{});

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		UpdateDrawFrame();
	}
#endif

	screenManager.Unload();
	UnloadResources();
	UnloadRenderTexture(target);
	CloseWindow();
	return 0;
}

void UpdateDrawFrame()
{
	screenManager.Update();

	BeginTextureMode(target);
	{
		ClearBackground(CLR_BLACK);
		screenManager.Draw();
	}
	EndTextureMode();

	BeginDrawing();
	{
		ClearBackground(BLACK);
		constexpr Vector2 origin{ 0.0f, 0.0f };
		DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, WHITE);
		DrawDebugData();
	}
	EndDrawing();
}
