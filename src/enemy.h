#pragma once

#include "enemy_pool.h"
#include "entity.h"
#include "event_bus.h"
#include "event_listener.h"
#include "screen.h"
#include "utils.h"
#include <iostream>
#include <raylib.h>

enum class EnemyPattern : unsigned char;
class Shake;

class Enemy final : public RenderedEntity, EventListener
{
	friend class EnemyPool;

public:
	Enemy() { EVENT_SUBSCRIBE }
	~Enemy() override { EVENT_UNSUBSCRIBE }

	void update(float delta) override;
	void draw(float delta) const override;
	void despawn();
	void notify(const Event &event) override;
	const char *getName() const override { return "Enemy"; }
	bool isActive() const override { return isActive_; }

private:
	void onInputUpdate(const InputUpdatedEvent &event);

	size_t id_        = 0;
	Vector2 position_ = { 0, 0 };
	Vector2 velocity_ = { 0, 0 };
	Rectangle bounds_ = { 0, 0, 0, 0 };
	String value_;
	size_t highlightOffset_ = 0;
	bool isActive_          = false;
	bool isDying_           = false;
	EnemyPattern pattern_   = (EnemyPattern)0;
	Shake *shake_{ nullptr };
};
