#pragma once
#include <string>
#include <vector>

#define E_BAIL(val, msg) TraceLog(LOG_ERROR, msg); return val;
#define E_PANIC(msg) TraceLog(LOG_FATAL, msg); exit(1);

using String = std::string;

std::vector<String> SplitString(const String &str, const String& delim);
void DrawDebugData(); // Draw the framerate in the topleft corner using a custom BMfont
