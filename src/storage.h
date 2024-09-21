#pragma once
#include "utils.h"

namespace storage
{
	enum class StorageData : unsigned char
	{
		MODE    = 0,
		HISCORE = 1,
	};

	bool saveStorageData(StorageData pos, unsigned long value);
	unsigned long loadStorageData(StorageData pos);
}