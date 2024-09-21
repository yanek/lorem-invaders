#pragma once

#include "utils.h"

class Screen;
class Entity
{
	friend class Screen;

public:
	virtual ~Entity() = default;
	virtual void update(float delta) {}
	virtual const char *getName() const = 0;
	virtual bool isActive() const { return true; }
	Screen *getScreen() const { return screen_; }

private:
	mutable Screen *screen_ = nullptr;
};

class RenderedEntity : public Entity
{
public:
	virtual void draw(float delta) const = 0;
	virtual unsigned char getLayer() const { return LAYER_DEFAULT; }

	static constexpr unsigned char LAYER_BACKGROUND = 0;
	static constexpr unsigned char LAYER_DEFAULT    = 1;
	static constexpr unsigned char LAYER_FOREGROUND = 2;
	static constexpr unsigned char LAYER_GUI        = 3;
};
