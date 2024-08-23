#pragma once

#include "event_bus.h"
#include "event_listener.h"
#include "screen.h"

class Shake;

class Player final : EventListener
{
public:
	Player() { EVENT_SUBSCRIBE }
	~Player() override { EVENT_UNSUBSCRIBE }

	void update(float delta);
	void draw() const;
	void damage();
	bool isDead() const { return hitpoints_ == 0; }
	void notify(const Event &event) override;

private:
	unsigned long score_{ 0 };
	unsigned char hitpoints_{ 3 };
	unsigned char maxHitpoints_{ 3 };
	Shake *shake_{ nullptr };
};
