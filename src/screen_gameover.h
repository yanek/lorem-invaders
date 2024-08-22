#pragma once

#include "screen.h"

class GameOverScreen final : public Screen
{
public:
	explicit GameOverScreen(unsigned long score);
	void Init() override;
	void Update() override;
	void Draw() override;
	void Unload() override;

private:
	unsigned long mScore;
};
