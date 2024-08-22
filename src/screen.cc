#include "screen.h"

ScreenManager screenManager{};

Screen::Screen(const std::string &name)
	: mName(name)
{
}

void ScreenManager::ChangeToScreen(Screen *newScreen)
{
	if (mCurrent != nullptr)
	{
		TraceLog(LOG_INFO, "Unloading screen %s", mCurrent->mName.c_str());
		mCurrent->Unload();
		delete mCurrent;
	}

	mCurrent = newScreen;
	mCurrent->Init();
	TraceLog(LOG_INFO, "Loading screen %s", mCurrent->mName.c_str());
}

void ScreenManager::Update() const
{
	mCurrent->Update();
}

void ScreenManager::Draw() const
{
	mCurrent->Draw();
}

void ScreenManager::Unload() const
{
	mCurrent->Unload();
	delete mCurrent;
}

Screen *ScreenManager::GetCurrent() const
{
	return mCurrent;
}
