#pragma once
#include <string>
#include <vector>

#define E_BAIL(val, msg) TraceLog(LOG_ERROR, msg); return val;
#define E_PANIC(msg) TraceLog(LOG_FATAL, msg); exit(1);

std::vector<std::string> SplitString(const std::string &str, const std::string& delim);
void DrawDebugData(); // Draw the framerate in the topleft corner using a custom BMfont
