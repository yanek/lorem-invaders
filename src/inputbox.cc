#include "inputbox.h"
#include "resources.h"
#include <raylib.h>

InputBox InitInputBox(const Rectangle rect)
{
	return InputBox{ rect, "\0", 0 };
}

void UpdateInputBox(InputBox *inputbox)
{
	int key = GetCharPressed();

	while (key > 0)
	{
		if ((key >= 32) && (key <= 125) && (inputbox->letterCount < MAX_INPUT_CHARS))
		{
			inputbox->value[inputbox->letterCount] = (char)key;
			inputbox->value[inputbox->letterCount + 1] = '\0';
			inputbox->letterCount++;
		};

		key = GetCharPressed();
	}

	if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
	{
		inputbox->letterCount--;
		if (inputbox->letterCount < 0)
			inputbox->letterCount = 0;
		inputbox->value[inputbox->letterCount] = '\0';
	}

	if (IsKeyPressed(KEY_ENTER))
	{
		inputbox->letterCount = 0;
		inputbox->value[0] = '\0';
	}
}

void DrawInputBox(const InputBox *inputbox, const int framecount)
{
	const float fntsize = static_cast<float>(res_font16.baseSize);
	const int txtlen = MeasureTextEx(res_font16, inputbox->value, res_font16.baseSize, 0).x;
	const Vector2 txtpos = {
		512.0f / 2.0f - (float)txtlen / 2.0f,
		inputbox->rect.y + 8.0f,
	};
	const Color fgclr = WHITE;
	const Color bgclr = BLACK;

	DrawRectangleRec(inputbox->rect, bgclr);
	DrawTextEx(res_font16, inputbox->value, Vector2{ txtpos.x, txtpos.y }, res_font16.baseSize, 0, fgclr);

	if ((framecount / 20 % 2 == 0) && (inputbox->letterCount < MAX_INPUT_CHARS))
		DrawText("|", txtpos.x + txtlen, txtpos.y, res_font16.baseSize, fgclr);
}