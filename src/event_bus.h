#pragma once

#include <vector>

class Event;
class EventListener;

class EventBus
{
public:
	void subscribe(EventListener *subscriber);
	void unsubscribe(EventListener *subscriber);
	void fire(const Event &event) const;

private:
	std::vector<EventListener *> subscribers_;
};
