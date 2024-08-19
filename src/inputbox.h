#pragma once

#include <raylib.h>

#define MAX_INPUT_CHARS 31

typedef struct InputBox
{
	Rectangle rect;
	char value[MAX_INPUT_CHARS + 1];
	int letterCount;
} InputBox;

InputBox InitInputBox(Rectangle rect);
void UpdateInputBox(InputBox* inputbox);
void DrawInputBox(const InputBox * inputbox, int framecount);