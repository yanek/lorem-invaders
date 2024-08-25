#pragma once
#include "utils.h"

namespace storage
{
	enum class StorageData : u8
	{
		MODE    = 0,
		HISCORE = 1,
	};

	bool saveStorageData(StorageData pos, u64 value);
	u64 loadStorageData(StorageData pos);
}