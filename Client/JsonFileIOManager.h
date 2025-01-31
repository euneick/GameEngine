#pragma once
#include "json/json.h"

class JsonFileIOManager
{
private:
	static JsonFileIOManager* m_pThis;

public:
	bool WriteToJsonFile(const char* filename, const char* buffer, int len);
	bool ReadFromJsonFile(const char* filename, char* buffer, int len);

	static JsonFileIOManager* GetInstance()
	{
		if (m_pThis == NULL)
			m_pThis = new JsonFileIOManager();

		return m_pThis;
	}

	static void DestroyInstance()
	{
		if (m_pThis)
		{
			delete m_pThis;
			m_pThis = NULL;
		}
	}

	JsonFileIOManager();
	~JsonFileIOManager();
};

