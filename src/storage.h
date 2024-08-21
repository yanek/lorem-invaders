#pragma once

namespace storage
{
	enum class StorageData
	{
		MODE = 0,
		HISCORE = 1,
	};

	bool SaveStorageData(StorageData pos, int value);
	int LoadStorageData(StorageData pos);
}