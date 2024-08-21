#include "colors.h"
#include "resources.h"
#include "screens.h"
#include "utils.h"
#include "viewport.h"
#include <raylib.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

static Viewport *viewport;

void UpdateDrawFrame();

int main()
{
	SetTraceLogLevel(LOG_TRACE);
	TraceLog(LOG_TRACE, "Starting game");
	viewport = new Viewport{};
	res::LoadResources();

	viewport->InitRenderTexture();
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
	res::UnloadResources();

	delete viewport;
	return 0;
}

void UpdateDrawFrame()
{
	screenManager.Update();

	viewport->BeginDrawing();
	{
		ClearBackground(color::nearBlack);
		screenManager.Draw();
	}
	viewport->EndDrawing();

	BeginDrawing();
	{
		ClearBackground(color::black);
		viewport->DrawRenderTexture();
		DrawDebugData();
	}
	EndDrawing();
}
