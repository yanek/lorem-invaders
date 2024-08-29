#pragma once

#include "utils.h"

class Screen;
class Entity
{
	friend class Screen;

public:
	virtual ~Entity() = default;
	virtual void update(f32 delta) {}
	virtual const char *getName() const = 0;
	virtual bool isActive() const { return true; }
	Screen *getScreen() const { return screen_; }

private:
	mutable Screen *screen_ = nullptr;
};

class RenderedEntity : public Entity
{
public:
	virtual void draw(f32 delta) const = 0;
	virtual u8 getLayer() const { return LAYER_DEFAULT; }

	static constexpr u8 LAYER_BACKGROUND = 0;
	static constexpr u8 LAYER_DEFAULT    = 1;
	static constexpr u8 LAYER_FOREGROUND = 2;
	static constexpr u8 LAYER_GUI        = 3;
};
