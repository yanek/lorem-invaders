#pragma once

#include "lipsum.h"
#include "screen.h"
#include "viewport.h"

class Player;
class EnemyPool;
class InputBox;

class GameScreen final : public Screen
{
public:
	explicit GameScreen(const GameMode mode)
		: lipsum_{ mode }, gameMode_{ mode } {}

	void init() override;
	void update() override;
	void draw() override;
	void unload() override;
	float getDifficultyModifier() const;
	Player *getPlayer() const;
	InputBox *getInputBox() const;
	const char *getName() const override { return "game_screen"; }

	static constexpr unsigned int SCORE_ZONE_1 = Viewport::GAME_HEIGHT / 3 + 32;
	static constexpr unsigned int SCORE_ZONE_2 = SCORE_ZONE_1 + SCORE_ZONE_1 - 32;

private:
	bool isPaused_ = false;
	float difficultyModifier_ = 1.0f;
	Player *player_{ nullptr };
	InputBox *inputBox_{ nullptr };
	Lipsum lipsum_;
	GameMode gameMode_;
	float spawnTimeout_ = 2.0f;
	float spawnElapsed_ = 0.0f;
};