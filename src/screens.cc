#include "screens.h"

ScreenManager screenManager = {};

void ScreenManager::ChangeToScreen(Screen *newScreen)
{
	TraceLog(LOG_INFO, "Unloading screen %s", this->current->GetName().c_str());
	this->current->Unload();
	delete this->current;
	this->current = newScreen;
	this->current->Init();
	TraceLog(LOG_INFO, "Loading screen %s", this->current->GetName().c_str());
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
