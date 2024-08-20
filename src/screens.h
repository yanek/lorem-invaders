#pragma once

#include "entity.h"
#include "inputbox.h"
#include "lipsum.h"
#include <string>

class Screen
{
public:
	virtual ~Screen() = default;
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Unload() = 0;
	virtual std::string GetName() = 0;
};

class TitleScreen final : public Screen
{
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Unload() override;
	std::string GetName() override { return "TitleScreen"; };
};

class GameScreen final : public Screen
{
public:
	void Init() override;
	void Update() override;
	void Draw() override;
	void Unload() override;
	std::string GetName() override { return "GameScreen"; };

private:
	int framecounter{ 0 };
	EnemyPool *enemyPool{ nullptr };
	InputBox *inputbox{ nullptr };
	Lipsum lipsum{};
};

class ScreenManager
{
public:
	void ChangeToScreen(Screen *newScreen);
	void Update() const;
	void Draw() const;
	void Unload() const;

private:
	Screen *current = new TitleScreen{};
};

extern ScreenManager screenManager;
