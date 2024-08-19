#pragma once

#include <raylib.h>

typedef enum GameScreen
{
    SCR_UNKNOWN = -1,
    SCR_TITLE = 0,
    SCR_GAME = 1
} GameScreen;

extern GameScreen currentScreen;
extern Font font;

void ChangeToScreen(int newScreen); // Change to a new screen without transition

// SCR_TITLE
void InitTitleScreen(void);
void UpdateTitleScreen(void);
void DrawTitleScreen(void);
void UnloadTitleScreen(void);

// SCR_GAME
void InitGameScreen(void);
void UpdateGameScreen(void);
void DrawGameScreen(void);
void UnloadGameScreen(void);