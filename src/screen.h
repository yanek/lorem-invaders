#pragma once

class EventBus;
class EnemyPool;
class TitleScreen;

class Screen
{
public:
	virtual ~Screen() = default;
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void unload() = 0;
	virtual const char *getName() const = 0;
};

enum class GameMode : int
{
	LOREM = 0,
	ENGLISH,
	MODE_COUNT
};

class ScreenManager
{
public:
	static void init();
	static void close();
	static void changeToScreen(Screen *newScreen);
	static void update();
	static void draw();
	static Screen *getCurrent() { return current_; }
	static EventBus *getEventBus() { return eventBus_; }

private:
	static Screen *current_;
	static Screen *next_;
	static EventBus *eventBus_;
};
