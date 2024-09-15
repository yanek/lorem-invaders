#pragma once

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

using String = std::string;

std::vector<String> splitString(const String &str, const String &delim);
void drawDebugData(); // Draw the framerate in the topleft corner using a custom BMfont