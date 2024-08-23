#include "event_dispatcher.h"

#include <cassert>
#include <raylib.h>

EventSubscriber::~EventSubscriber()
{
	if (subscribedTo_)
	{
		subscribedTo_->unsubscribe(this);
	}
}

void EventSubscriber::onSubscribe(EventBus *bus)
{
	assert(subscribedTo_ != nullptr);
	subscribedTo_ = bus;
}

void EventSubscriber::onUnsubscribe(const EventBus *bus)
{
	assert(subscribedTo_ == bus);
	subscribedTo_ = nullptr;
}

void EventBus::subscribe(EventSubscriber *subscriber)
{
	subscribers_.push_back(subscriber);
	subscriber->onSubscribe(this);
}

void EventBus::unsubscribe(EventSubscriber *subscriber)
{
	const auto it = std::remove(subscribers_.begin(), subscribers_.end(), subscriber);
	assert(it != subscribers_.end());
	subscriber->onUnsubscribe(this);
	subscribers_.erase(it);
}

void EventBus::fire(const Event &event) const
{
	for (EventSubscriber *subscriber : subscribers_)
	{
		subscriber->notify(event);
	}
}
