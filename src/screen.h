#pragma once

#include "inputbox.h"
#include "lipsum.h"
#include "player.h"
#include <string>

class EnemyPool;
class TitleScreen;

class Screen
{
public:
	virtual ~Screen() = default;
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Unload() = 0;
	const std::string name;

protected:
	explicit Screen(const std::string &name);
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
	void ChangeToScreen(Screen *newScreen);
	void Update() const;
	void Draw() const;
	void Unload() const;
	Screen *GetCurrent() const;

private:
	Screen *current{ nullptr };
};

extern ScreenManager screenManager;
