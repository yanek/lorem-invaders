#pragma once

#include "screen.h"

class TitleScreen final : public Screen
{
public:
	TitleScreen();
	void Init() override;
	void Update() override;
	void Draw() override;
	void Unload() override;

private:
	GameMode mMode{ GameMode::LOREM };
	int mHiscore;
};