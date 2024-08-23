#pragma once

namespace storage
{
	enum class StorageData
	{
		MODE = 0,
		HISCORE = 1,
	};

	bool saveStorageData(StorageData pos, int value);
	int loadStorageData(StorageData pos);
}