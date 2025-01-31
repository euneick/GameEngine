#include "JsonFileIOManager.h"


JsonFileIOManager* JsonFileIOManager::m_pThis = NULL;

JsonFileIOManager::JsonFileIOManager()
{
}


JsonFileIOManager::~JsonFileIOManager()
{
}

bool JsonFileIOManager::WriteToJsonFile(const char* filename, const char* buffer, int len)
{
	FILE* fp = nullptr;
	fopen_s(&fp, filename, "wb");

	if (fp == nullptr)
	{
		return false;
	}

	size_t fileSize = fwrite(buffer, 1, len, fp);

	fclose(fp);

	return true;
}

bool JsonFileIOManager::ReadFromJsonFile(const char* filename, char* buffer, int len)
{
	FILE* fp = nullptr;
	fopen_s(&fp, filename, "rb");

	if (fp == nullptr)
	{
		return false;
	}

	size_t fileSize = fread(buffer, 1, len, fp);

	fclose(fp);

	return true;
}