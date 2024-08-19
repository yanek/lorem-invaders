#pragma once

typedef enum GameScreen
{
    SCR_UNKNOWN = -1,
    SCR_TITLE = 0,
    SCR_GAME = 1
} GameScreen;

extern GameScreen currentScreen;

void ChangeToScreen(GameScreen newScreen); // Change to a new screen without transition

// SCR_TITLE
void InitTitleScreen();
void UpdateTitleScreen();
void DrawTitleScreen();
void UnloadTitleScreen();

// SCR_GAME
void InitGameScreen();
void UpdateGameScreen();
void DrawGameScreen();
void UnloadGameScreen();