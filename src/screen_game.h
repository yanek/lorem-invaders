#pragma once

#include "screen.h"
#include "viewport.h"

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
	float GetDifficultyModifier() const;
	Player *GetPlayer() const;
	EnemyPool *GetEnemyPool() const;
	InputBox *GetInputBox() const;

	static constexpr unsigned int kScoreZone1 = Viewport::kGameHeight / 3 + 32;
	static constexpr unsigned int kScoreZone2 = kScoreZone1 + kScoreZone1 - 32;

private:
	int mFramecounter = 0;
	bool mIsPaused = false;
	float mDifficultyModifier = 1.0f;
	Player *mPlayer{ nullptr };
	EnemyPool *mEnemyPool{ nullptr };
	InputBox *mInputBox{ nullptr };
	Lipsum mLipsum;
	GameMode mMode;
};