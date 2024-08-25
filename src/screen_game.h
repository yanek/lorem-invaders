#pragma once

#include "event_bus.h"
#include "event_listener.h"
#include "lipsum.h"
#include "screen.h"
#include "viewport.h"

class Player;
class EnemyPool;
class InputBox;

class GameScreen final : public Screen, public EventListener
{
public:
	explicit GameScreen(const GameMode mode)
		: lipsum_{ mode }, gameMode_{ mode } { EVENT_SUBSCRIBE }
	~GameScreen() override{ EVENT_UNSUBSCRIBE };

	void init() override;
	void update(float delta) override;
	void draw(float delta) override;
	void unload() override;
	float getDifficultyModifier() const;
	const char *getName() const override { return "GameScreen"; }
	void notify(const Event &event) override;

	static constexpr unsigned int SCORE_ZONE_1 = Viewport::GAME_HEIGHT / 3 + 32;
	static constexpr unsigned int SCORE_ZONE_2 = SCORE_ZONE_1 + SCORE_ZONE_1 - 32;

private:
	float difficultyModifier_ = 1.0f;
	Lipsum lipsum_;
	GameMode gameMode_;
	EnemyPool *enemyPool_ = nullptr;
	float spawnTimeout_   = 2.0f;
	float spawnElapsed_   = 0.0f;
};