#pragma once

#include "enemy_pool.h"
#include "event_bus.h"
#include "event_listener.h"
#include "screen.h"

#include <iostream>
#include <raylib.h>

enum class EnemyPattern;
class Shake;

class Enemy final : EventListener
{
	friend class EnemyPool;

public:
	Enemy() { EVENT_SUBSCRIBE }
	~Enemy() override { EVENT_UNSUBSCRIBE }

	void update(const GameScreen *screen, float delta);
	void draw() const;
	void despawn();
	void notify(const Event &event) override;

private:
	void onInputUpdate(const InputUpdatedEvent &event);

	size_t id_ = 0;
	Vector2 position_ = { 0, 0 };
	Vector2 velocity_ = { 0, 0 };
	std::string value_ = "";
	size_t highlightOffset_ = 0;
	bool isActive_ = false;
	bool isDying_ = false;
	EnemyPattern pattern_ = (EnemyPattern)0;
	Shake *shake_{ nullptr };
};
