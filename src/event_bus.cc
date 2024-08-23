#include "event_bus.h"
#include "event_listener.h"
#include <cassert>
#include <raylib.h>

void EventBus::subscribe(EventListener *subscriber)
{
	subscribers_.push_back(subscriber);
	subscriber->onSubscribe(this);
}

void EventBus::unsubscribe(EventListener *subscriber)
{
	const auto it = std::remove(subscribers_.begin(), subscribers_.end(), subscriber);
	assert(it != subscribers_.end());
	subscriber->onUnsubscribe(this);
	subscribers_.erase(it);
}

void EventBus::fire(const Event &event) const
{
	for (EventListener *subscriber : subscribers_)
	{
		subscriber->notify(event);
	}
}
