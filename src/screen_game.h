#pragma once

#include "screen.h"

class Player;
class EnemyPool;
class InputBox;

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
	int mFramecounter = 0;
	bool mIsPaused = false;
	Player *mPlayer{ nullptr };
	EnemyPool *mEnemyPool{ nullptr };
	InputBox *mInputBox{ nullptr };
	Lipsum mLipsum;
	GameMode mMode;
};