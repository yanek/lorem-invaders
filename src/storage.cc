#include "storage.h"
#include <raylib.h>
#include <string>

const std::string storageFile = "save.dat";

bool storage::saveStorageData(StorageData pos, const unsigned long value)
{
	bool success            = false;
	int dataSize            = 0;
	unsigned char *fileData = LoadFileData(storageFile.c_str(), &dataSize);
	const int position      = (int)pos;

	if (fileData != nullptr)
	{
		unsigned int newDataSize   = 0;
		unsigned char *newFileData = nullptr;
		if (dataSize <= (position * sizeof(int)))
		{
			// Increase data size up to position and store value
			newDataSize = (position + 1) * sizeof(int);
			newFileData = static_cast<unsigned char *>(RL_REALLOC(fileData, newDataSize));

			if (newFileData != nullptr)
			{
				// RL_REALLOC succeeded
				const auto dataPtr = reinterpret_cast<int *>(newFileData);
				dataPtr[position]  = (int)value;
			}
			else
			{
				// RL_REALLOC failed
				TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to realloc data (%u), position in bytes (%u) bigger than actual file size", storageFile.c_str(), dataSize, position * sizeof(int));

				// We store the old size of the file
				newFileData = fileData;
				newDataSize = dataSize;
			}
		}
		else
		{
			// Store the old size of the file
			newFileData = fileData;
			newDataSize = dataSize;

			// Replace value on selected position
			const auto dataPtr = reinterpret_cast<int *>(newFileData);
			dataPtr[position]  = value;
		}

		success = SaveFileData(storageFile.c_str(), newFileData, newDataSize);
		RL_FREE(newFileData);

		TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", storageFile.c_str(), value);
	}
	else
	{
		TraceLog(LOG_INFO, "FILEIO: [%s] File created successfully", storageFile.c_str());

		dataSize           = (position + 1) * sizeof(int);
		fileData           = static_cast<unsigned char *>(RL_MALLOC(dataSize));
		const auto dataPtr = reinterpret_cast<int *>(fileData);
		dataPtr[position]  = value;

		success = SaveFileData(storageFile.c_str(), fileData, dataSize);
		UnloadFileData(fileData);

		TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", storageFile.c_str(), value);
	}

	return success;
}

unsigned long storage::loadStorageData(StorageData pos)
{
	unsigned long value     = 0;
	int dataSize            = 0;
	unsigned char *fileData = LoadFileData(storageFile.c_str(), &dataSize);
	const int position      = static_cast<int>(pos);

	if (fileData != nullptr)
	{
		if (dataSize < position * 4)
			TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to find storage position: %i", storageFile.c_str(), position);
		else
		{
			const int *dataPtr = reinterpret_cast<int *>(fileData);
			value              = dataPtr[position];
		}

		UnloadFileData(fileData);
		TraceLog(LOG_INFO, "FILEIO: [%s] Loaded storage value: %i", storageFile.c_str(), value);
	}

	return value;
}