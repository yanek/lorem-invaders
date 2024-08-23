#include "screen.h"

#include "event_dispatcher.h"
#include "screen_title.h"
#include <raylib.h>

Screen *ScreenManager::current_ = nullptr;
EventBus *ScreenManager::eventBus_ = nullptr;

void ScreenManager::init()
{
	eventBus_ = new EventBus{};
	changeToScreen(new TitleScreen{});
}

void ScreenManager::changeToScreen(Screen *newScreen)
{
	if (current_ != nullptr)
	{
		TraceLog(LOG_INFO, "Unloading screen %s", current_->getName());
		current_->unload();
		delete current_;
	}

	current_ = newScreen;
	current_->init();
	TraceLog(LOG_INFO, "Loading screen %s", current_->getName());
}

void ScreenManager::update()
{
	current_->update();
}

void ScreenManager::draw()
{
	current_->draw();
}

void ScreenManager::close()
{
	current_->unload();
	delete current_;
	current_ = nullptr;
	delete eventBus_;
	eventBus_ = nullptr;
}