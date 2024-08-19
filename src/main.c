#include <raylib.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include "screens.h"
#include "colors.h"
#include "utils.h"

const int virtualScreenWidth = 512;
const int virtualScreenHeight = 448;
const int screenWidth = 1024;
const int screenHeight = 768;
float virtualRatio = 0.0f;
RenderTexture2D target = { 0 };
Rectangle sourceRec = { 0 };
Rectangle destRec = { 0 };

void UpdateDrawFrame(void);

int main(void)
{
	SetTraceLogLevel(LOG_TRACE);
	TraceLog(LOG_TRACE, "Starting game");
	InitWindow(screenWidth, screenHeight, "Lorem Invader");

	target = LoadRenderTexture(virtualScreenWidth, virtualScreenHeight);
	virtualRatio = (float)screenWidth / (float)virtualScreenWidth;
	sourceRec = (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height };
	destRec = (Rectangle){ -virtualRatio, -virtualRatio, (float)screenWidth + virtualRatio * 2, (float)screenHeight + virtualRatio * 2 };

	font = LoadFont("resources/ibm-16.fnt");
	SetTextLineSpacing(16);

	currentScreen = SCR_TITLE;
	InitTitleScreen();

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		UpdateDrawFrame();
	}
#endif

	switch (currentScreen)
	{
	case SCR_TITLE:
		UnloadTitleScreen();
		break;
	case SCR_GAME:
		UnloadGameScreen();
		break;
	default:
		TraceLog(LOG_ERROR, "Cannot unload unknown screen");
		break;
	}

	UnloadFont(font);

	UnloadRenderTexture(target);
	CloseWindow();
	return 0;
}

void UpdateDrawFrame()
{
	switch (currentScreen)
	{
	case SCR_TITLE:
		UpdateTitleScreen();
		break;
	case SCR_GAME:
		UpdateGameScreen();
		break;
	default:
		TraceLog(LOG_ERROR, "Cannot update unknown screen");
		break;
	}

	BeginTextureMode(target);
	{
		ClearBackground(CLR_BLACK);

		switch (currentScreen)
		{
		case SCR_TITLE:
			DrawTitleScreen();
			break;
		case SCR_GAME:
			DrawGameScreen();
			break;
		default:
			TraceLog(LOG_ERROR, "Cannot draw unknown screen");
			break;
		}

	}
	EndTextureMode();

	BeginDrawing();
	{
		ClearBackground(BLACK);
		const Vector2 origin = { 0.0f, 0.0f };
		DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, WHITE);
		DrawDebugData();
	}
	EndDrawing();
}