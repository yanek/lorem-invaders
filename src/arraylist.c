#include "arraylist.h"
#include "utils.h"
#include <raylib.h>
#include <stdlib.h>
#include <string.h>

#define MSG_MEMALLOC "Could not allocate memory for List"
#define MSG_INDEX_OOB "Index out of bounds"
#define MSG_EMPTY_LIST "List is empty"

ArrayList *CreateArrayList(const size_t itemSize, const size_t initialCapacity)
{
	ArrayList *arr = malloc(sizeof(ArrayList));

	if (!arr)
	{
		E_BAIL(NULL, MSG_MEMALLOC);
	}

	arr->itemSize = itemSize;
	arr->capacity = initialCapacity;
	arr->len = 0;
	arr->items = malloc(itemSize * initialCapacity);

	if (!arr->items)
	{
		E_BAIL(NULL, MSG_MEMALLOC);
	}

	return arr;
}

size_t AddArrayListItem(ArrayList *arr, const void *item)
{
	if (arr->len == arr->capacity)
	{
		arr->capacity = arr->capacity > 0 ? arr->capacity * 2 : 1;
		void *items = realloc(arr->items, arr->itemSize * arr->capacity);

		if (!items)
		{
			E_BAIL(-1, MSG_MEMALLOC);
		}

		arr->items = items;
	}

	const size_t index = arr->len++;
	memcpy((unsigned char *)arr->items + index * arr->itemSize, item, arr->itemSize);

	return index;
}

void *GetArrayListItem(const ArrayList *arr, const size_t index)
{
	if (index >= arr->len)
	{
		E_BAIL(NULL, MSG_INDEX_OOB);
	}

	return (unsigned char *)arr->items + index * arr->itemSize;
}

unsigned char RemoveArrayListItem(ArrayList *arr, const size_t index)
{
	if (arr->len == 0)
	{
		E_BAIL(1, MSG_EMPTY_LIST);
	}

	if (index >= arr->len)
	{
		E_BAIL(1, MSG_INDEX_OOB);
	}

	if (arr->len == 1)
	{
		arr->len = 0;
		return 0;
	}

	--arr->len;

	unsigned char *itemPtr = (unsigned char *)arr->items + index * arr->itemSize;
	const unsigned char *endPtr = (unsigned char *)arr->items + arr->len * arr->itemSize;
	memcpy(itemPtr, endPtr, arr->itemSize);

	return 0;
}