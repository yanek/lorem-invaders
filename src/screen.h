#pragma once

#include "utils.h"
#include "viewport.h"
#include <vector>

class RenderedEntity;
class Entity;
class EventBus;
class EnemyPool;
class TitleScreen;

enum class GameMode : unsigned char
{
	LOREM = 0,
	ENGLISH,
	NUM_MODES
};

class Screen
{
	friend class ScreenManager;

public:
	virtual ~Screen()   = default;
	virtual void init() = 0;
	virtual void update(float delta) {}
	virtual void draw(float delta) {}
	virtual void unload() {}
	virtual const char *getName() const = 0;
	void destroyEntity(Entity *entity);
	void clearEntities();
	void sortRendered_();
	bool isPaused() const { return isPaused_; }
	bool setPaused(const bool paused) { return isPaused_ = paused; }

	template <class EntityType>
	EntityType *createEntity()
	{
		EntityType *e = new EntityType{};
		addEntity_(e);
		return e;
	}

private:
	void addEntity_(Entity *entity);
	bool isPaused_              = false;
	bool isRenderableListDirty_ = true;
	std::vector<Entity *> entities_;
	std::vector<RenderedEntity *> renderables_;
};

class ScreenManager
{
public:
	static void init(Viewport *viewport);
	static void close();
	static void changeToScreen(Screen *newScreen);
	static void update();
	static Screen *getCurrent() { return current_; }
	static EventBus *getEventBus() { return eventBus_; }

private:
	static Screen *current_;
	static Screen *next_;
	static EventBus *eventBus_;
	static Viewport *viewport_;
};
