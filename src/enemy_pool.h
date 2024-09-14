#pragma once

#include <utility>

#include "entity.h"
#include "utils.h"

class Lipsum;
class Screen;
class GameScreen;
class Enemy;

enum class EnemyPattern : u8
{
    SLOW = 0,
    FAST,
    FASTER,
    DOUBLE,
    TRIPLE,
    BONUS,
    NUM_PATTERNS
};

struct SpawnData final
{
    SpawnData(const Vector2 position, const Vector2 velocity, String value)
        : position(position), velocity(velocity), value(std::move(value))
    {
    }

    Vector2 position;
    Vector2 velocity;
    String value;
};

class EnemyPool final : public Entity
{
public:
    void init();
    void spawn(Lipsum& lipsum) const;
    Enemy* getEnemy(i32 id) const;
    void update(f32 delta) override;
    const char* getName() const override { return "EnemyPool"; }

private:
    static constexpr u8 MAX_POOLED = 16;
    Enemy* pool_[MAX_POOLED] = {};
};
