#pragma once

#include "event_bus.h"
#include "event_listener.h"
#include "lipsum.h"
#include "screen.h"

class Player;
class EnemyPool;
class InputBox;

class GameScreen final : public Screen, public EventListener
{
public:
    explicit GameScreen(const GameMode mode)
        : lipsum_{mode}, gameMode_{mode} { EVENT_SUBSCRIBE }

    ~GameScreen() override { EVENT_UNSUBSCRIBE };

    void init() override;
    void update(f32 delta) override;
    void draw(f32 delta) override;
    void unload() override;
    u8 getDifficultyModifier() const;
    const char* getName() const override { return "GameScreen"; }
    void notify(const Event& event) override;

private:
    u8 difficultyModifier_ = 0;
    Lipsum lipsum_;
    GameMode gameMode_;
    EnemyPool* enemyPool_ = nullptr;
    f32 spawnTimeout_ = 2.0f;
    f32 spawnElapsed_ = 0.0f;
};
