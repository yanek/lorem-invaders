#pragma once

#include "screen.h"

class GameScreen final : public Screen
{
public:
	explicit GameScreen(GameMode mode);
	void Init() override;
	void Update() override;
	void Draw() override;
	void Unload() override;
	Player *GetPlayer() const;
	EnemyPool *GetEnemyPool() const;
	InputBox *GetInputBox() const;

private:
	int framecounter{ 0 };
	Player *player{ nullptr };
	EnemyPool *enemyPool{ nullptr };
	InputBox *inputbox{ nullptr };
	Lipsum lipsum;
};