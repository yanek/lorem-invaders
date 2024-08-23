#include "audio.h"
#include "colors.h"
#include "resources.h"
#include "screen.h"
#include "utils.h"
#include "viewport.h"
#include <raylib.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

static Viewport *viewport;
static void updateDrawFrame();
static bool shouldClose();

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

	ScreenManager::init();

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
	SetTargetFPS(60);

	while (!shouldClose())
	{
		updateDrawFrame();
	}
#endif

	Audio::close();
	ScreenManager::close();
	res::UnloadResources();

	delete viewport;
	return 0;
}

void updateDrawFrame()
{
	ScreenManager::update();
	Audio::update();

	viewport->BeginDrawing();
	{
		ClearBackground(color::background);
		ScreenManager::draw();
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

bool shouldClose()
{
	const char* currentScreen = ScreenManager::getCurrent()->getName();
	const bool escKeyPressed = (currentScreen == "title_screen") && IsKeyPressed(KEY_ESCAPE);
	return WindowShouldClose() || escKeyPressed;
}