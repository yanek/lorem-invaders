#pragma once

#include "utils.h"

enum class EventType
{
	None = 0,
	ApplicationExit,
	InputUpdated,
	EnemyKilled,
	PlayerHurt,
	PlayerHealed,
};

/* clang-format off */
#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; } \
							   virtual EventType getEventType() const override { return getStaticType(); } \
							   virtual const char *getName() const override { return #type; }
/* clang-format on */

class Event
{
public:
	virtual ~Event() = default;
	virtual EventType getEventType() const = 0;
	virtual const char *getName() const = 0;
};

class ApplicationExitEvent final : public Event
{
public:
	EVENT_CLASS_TYPE(ApplicationExit)
};

class InputUpdatedEvent final : public Event
{
public:
	explicit InputUpdatedEvent(const char *value)
		: value(value) {}

	EVENT_CLASS_TYPE(InputUpdated);
	const char *value;
};

class EnemyKilledEvent final : public Event
{
public:
	EnemyKilledEvent(const u32 letterCount, const f32 verticalPosition)
		: letterCount(letterCount),
		  verticalPosition(verticalPosition) {}

	EVENT_CLASS_TYPE(EnemyKilled)
	const u32 letterCount;
	const f32 verticalPosition;
};

class PlayerHurtEvent final : public Event
{
public:
	EVENT_CLASS_TYPE(PlayerHurt);
};

class PlayerHealedEvent final : public Event
{
public:
	EVENT_CLASS_TYPE(PlayerHealed);
};
