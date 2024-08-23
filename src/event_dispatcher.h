#pragma once

#include "event.h"
#include <vector>

class EventSubscriber;
class EventBus
{
public:
	void subscribe(EventSubscriber *subscriber);
	void unsubscribe(EventSubscriber *subscriber);
	void fire(const Event &event) const;

private:
	std::vector<EventSubscriber *> subscribers_;
};

class EventSubscriber
{
public:
	virtual ~EventSubscriber();
	virtual void notify(const Event &event) = 0;

private:
	friend class EventBus;
	void onSubscribe(EventBus *bus);
	void onUnsubscribe(const EventBus *bus);
	EventBus *subscribedTo_;
};