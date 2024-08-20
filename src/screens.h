#pragma once

#include "inputbox.h"
#include "lipsum.h"
#include "player.h"
#include <string>

class EnemyPool;

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

class TitleScreen final : public Screen
{
public:
	TitleScreen();
	void Init() override;
	void Update() override;
	void Draw() override;
	void Unload() override;
};

class GameScreen final : public Screen
{
public:
	GameScreen();
	void Init() override;
	void Update() override;
	void Draw() override;
	void Unload() override;
	Player *GetPlayer() const;
	EnemyPool *GetEnemyPool();
	InputBox *GetInputBox() const;

private:
	int framecounter{ 0 };
	Player *player{ nullptr };
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
