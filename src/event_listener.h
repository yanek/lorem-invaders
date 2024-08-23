#pragma once

#include "event.h"

#define EVENT_SUBSCRIBE   ScreenManager::getEventBus()->subscribe(this);
#define EVENT_UNSUBSCRIBE ScreenManager::getEventBus()->unsubscribe(this);

class EventListener
{
public:
	virtual ~EventListener();
	virtual void notify(const Event &event) = 0;

private:
	friend class EventBus;
	void onSubscribe(EventBus *bus);
	void onUnsubscribe(const EventBus *bus);
	EventBus *subscribedTo_;
};