#pragma once
#include <raylib.h>
#include <string>
#include <vector>

#define VERSION_MAJOR 0
#define VERSION_MINOR 5
#define VERSION_PATCH 1

#define E_BAIL(val, ...)              \
	TraceLog(LOG_ERROR, __VA_ARGS__); \
	return val;

#define E_PANIC(...)                  \
	TraceLog(LOG_FATAL, __VA_ARGS__); \
	exit(1);

using i8     = int8_t;
using i16    = int16_t;
using i32    = int32_t;
using i64    = int64_t;
using u8     = uint8_t;
using u16    = uint16_t;
using u32    = uint32_t;
using u64    = uint64_t;
using f32    = float;
using f64    = double;
using usize  = size_t;
using String = std::string;

std::vector<String> splitString(const String &str, const String &delim);
void drawDebugData(); // Draw the framerate in the topleft corner using a custom BMfont

struct Vec2 : Vector2
{
	void add(const Vec2 &other)
	{
		x += other.x;
		y += other.y;
	};
};