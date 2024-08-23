#pragma once

enum class EventType
{
	None = 0,
	ApplicationExit,
	EnemyKilled,
	PlayerHurt,
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

class EnemyKilledEvent final : public Event
{
public:
	EnemyKilledEvent(const unsigned int letterCount, const float verticalPosition)
		: letterCount(letterCount),
		  verticalPosition(verticalPosition) {}

	EVENT_CLASS_TYPE(EnemyKilled)
	const unsigned int letterCount;
	const float verticalPosition;
};

class PlayerHurtEvent final : public Event
{
public:
	EVENT_CLASS_TYPE(PlayerHurt);
};