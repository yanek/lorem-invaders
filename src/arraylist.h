#pragma once

#include <stdio.h>

typedef struct
{
	size_t len;
	size_t capacity;
	size_t itemSize;
	void *items;
} ArrayList;

ArrayList *CreateArrayList(size_t itemSize, size_t initialCapacity); // Create a new list
size_t AddArrayListItem(ArrayList *arr, const void *item);           // Append an item to the list, returns the index of the item
void *GetArrayListItem(const ArrayList *arr, size_t index);          // Get an item from the list, returns a pointer to the item
unsigned char RemoveArrayListItem(ArrayList *arr, size_t index);     // Remove an item from the list, returns 1 if successful, 0 otherwise
