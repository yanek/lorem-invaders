#include "screens.h"

ScreenManager screenManager = {};

Screen::Screen(const std::string &name)
	: name(name)
{
}

void ScreenManager::ChangeToScreen(Screen *newScreen)
{
	TraceLog(LOG_INFO, "Unloading screen %s", this->current->name.c_str());
	this->current->Unload();
	delete this->current;
	this->current = newScreen;
	this->current->Init();
	TraceLog(LOG_INFO, "Loading screen %s", this->current->name.c_str());
}

void ScreenManager::Update() const
{
	this->current->Update();
}

void ScreenManager::Draw() const
{
	this->current->Draw();
}

void ScreenManager::Unload() const
{
	this->current->Unload();
	delete this->current;
}

Screen *ScreenManager::GetCurrent() const
{
	return this->current;
}
