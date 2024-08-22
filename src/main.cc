#include "audio.h"
#include "colors.h"
#include "resources.h"
#include "screen.h"
#include "screen_title.h"
#include "utils.h"
#include "viewport.h"
#include <raylib.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

static Viewport *viewport;
static void UpdateDrawFrame();
static bool ShouldClose();

int main()
{
	SetTraceLogLevel(LOG_TRACE);
	TraceLog(LOG_TRACE, "Starting game");
	viewport = new Viewport{};
	Audio::init();
	res::LoadResources();

	viewport->InitRenderTexture();

	SetExitKey(0);
	SetTextLineSpacing(16);

	screenManager.ChangeToScreen(new TitleScreen{});

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
	SetTargetFPS(60);

	while (!ShouldClose())
	{
		UpdateDrawFrame();
	}
#endif

	Audio::close();
	screenManager.Unload();
	res::UnloadResources();

	delete viewport;
	return 0;
}

void UpdateDrawFrame()
{
	screenManager.Update();
	Audio::update();

	viewport->BeginDrawing();
	{
		ClearBackground(color::background);
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

bool ShouldClose()
{
	return WindowShouldClose() || ((screenManager.GetCurrent()->mName == "title_screen") && IsKeyPressed(KEY_ESCAPE));
}