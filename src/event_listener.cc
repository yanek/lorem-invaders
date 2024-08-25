#include "event_listener.h"

#include "event_bus.h"
#include <cassert>

EventListener::~EventListener()
{
	if (subscribedTo_)
	{
		subscribedTo_->unsubscribe(this);
	}
}

void EventListener::onSubscribe(EventBus *bus)
{
	assert(subscribedTo_ != nullptr);
	subscribedTo_ = bus;
}

void EventListener::onUnsubscribe(const EventBus *bus)
{
	assert(subscribedTo_ == bus);
	subscribedTo_ = nullptr;
}
