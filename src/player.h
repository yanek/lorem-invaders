#pragma once

#include "entity.h"
#include "event_bus.h"
#include "event_listener.h"
#include "screen.h"

class Shake;

class Player final : public RenderedEntity, EventListener
{
public:
	Player() { EVENT_SUBSCRIBE }
	~Player() override { EVENT_UNSUBSCRIBE }

	void update(f32 delta) override;
	void draw(f32 delta) const override;
	void damage();
	bool isDead() const { return hitpoints_ == 0; }
	void notify(const Event &event) override;
	const char *getName() const override { return "Player"; };
	u8 getLayer() const override { return LAYER_GUI; }

private:
	u64 score_{ 0 };
	u8 hitpoints_{ 3 };
	u8 maxHitpoints_{ 3 };
	Shake *shake_{ nullptr };
};
