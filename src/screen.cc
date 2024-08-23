#include "screen.h"

#include "event_bus.h"
#include "screen_title.h"

#include <cassert>
#include <raylib.h>

Screen *ScreenManager::current_ = nullptr;
Screen *ScreenManager::next_ = nullptr;
EventBus *ScreenManager::eventBus_ = nullptr;

void ScreenManager::init()
{
	eventBus_ = new EventBus{};
	changeToScreen(new TitleScreen{});
}

void ScreenManager::changeToScreen(Screen *newScreen)
{
	assert(next_ == nullptr);
	next_ = newScreen;
}

void ScreenManager::update()
{
	if (next_ != nullptr)
	{
		if (current_ != nullptr)
		{
			TraceLog(LOG_INFO, "Unloading screen %s", current_->getName());
			current_->unload();
			delete current_;
		}

		current_ = next_;
		next_ = nullptr;
		current_->init();
		TraceLog(LOG_INFO, "Loading screen %s", current_->getName());
	}

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