#pragma once
#include <cstdint>

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
	virtual uint8_t getLayer() const { return 0; }
};
