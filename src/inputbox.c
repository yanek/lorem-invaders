#include "inputbox.h"
#include <raylib.h>
#include "resources.h"

Font res_font16;

InputBox InitInputBox(const Rectangle rect)
{
	return (InputBox){
		.rect = rect,
		.value = "\0",
		.letterCount = 0,
	};
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
	const int txtlen = MeasureTextEx(res_font16, inputbox->value, res_font16.baseSize, 0).x;
	const Vector2 txtpos = {
		512 / 2 - txtlen / 2,
		(int)inputbox->rect.y + 8
	};
	const Color fgclr = WHITE;
	const Color bgclr = BLACK;

	DrawRectangleRec(inputbox->rect, bgclr);
	DrawTextEx(res_font16, inputbox->value, (Vector2){ txtpos.x, txtpos.y }, res_font16.baseSize, 0, fgclr);

	if ((framecount / 20 % 2 == 0) && (inputbox->letterCount < MAX_INPUT_CHARS))
		DrawText("|", txtpos.x + txtlen, txtpos.y, res_font16.baseSize, fgclr);
}