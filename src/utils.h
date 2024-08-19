#pragma once

#define MIN(i, j) (((i) < (j)) ? (i) : (j)) // Get the minimum of two values
#define MAX(i, j) (((i) > (j)) ? (i) : (j)) // Get the maximum of two values

#define E_BAIL(val, msg) TraceLog(LOG_ERROR, msg); return val
#define E_PANIC(msg) TraceLog(LOG_FATAL, msg); exit(1)

char* IntegerToText(int val); // Convert an integer to a string
void DrawDebugData(); // Draw the framerate in the topleft corner using a custom BMfont
