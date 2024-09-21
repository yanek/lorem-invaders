#include "audio.h"
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
	viewport = new Viewport{};
	viewport->initRenderTexture();

#ifdef NDEBUG
	SetTraceLogLevel(LOG_INFO);
#else
	SetTraceLogLevel(LOG_ALL);
#endif

	SetExitKey(0);
	SetTextLineSpacing(16);

	Audio::init();
	Resources::preload();
	ScreenManager::init(viewport);

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
	SetTargetFPS(60);
	while (!shouldClose())
		updateDrawFrame();
#endif

	ScreenManager::close();
	Resources::unload();
	Audio::close();

	delete viewport;
	return 0;
}

void updateDrawFrame()
{
	ScreenManager::update();
	Audio::update();
}

bool shouldClose()
{
	const Screen *currentScreen = ScreenManager::getCurrent();
	if (currentScreen == nullptr) return false;
	const bool escKeyPressed = (strcmp(currentScreen->getName(), "TitleScreen") == 0) && IsKeyPressed(KEY_ESCAPE);
	return WindowShouldClose() || escKeyPressed;
}