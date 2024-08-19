#include "inputbox.h"
#include <raylib.h>

InputBox InitInputBox(const Rectangle rect, Font *font)
{
	return (InputBox){
		.rect = rect,
		.value = "\0",
		.letterCount = 0,
		.font = font
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
	const int txtlen = MeasureTextEx(*inputbox->font, inputbox->value, inputbox->font->baseSize, 0).x;
	const Vector2 txtpos = {
		512 / 2 - txtlen / 2,
		(int)inputbox->rect.y + 8
	};
	const Color fgclr = WHITE;
	const Color bgclr = BLACK;

	DrawRectangleRec(inputbox->rect, bgclr);
	DrawTextEx(*inputbox->font, inputbox->value, (Vector2){ txtpos.x, txtpos.y }, inputbox->font->baseSize, 0, fgclr);

	if ((framecount / 20 % 2 == 0) && (inputbox->letterCount < MAX_INPUT_CHARS))
		DrawText("|", txtpos.x + txtlen, txtpos.y, inputbox->font->baseSize, fgclr);
}