#include "TimeManager.h"


namespace Euneick
{
	TimeManager::TimeManager()
	{
	}


	TimeManager::~TimeManager()
	{
	}

	void TimeManager::init(bool _useFPS, int _iFPS)
	{
		m_bPause = false;
		m_bUseFPS = _useFPS;
		m_iFPS = _iFPS;

		m_dwLastTime = GetTickCount();
		m_dwCurTime = GetTickCount();
		m_fElapseTime = 0.0f;
		m_fGameSpeed = 1.0f;
	}

	void TimeManager::Update()
	{
		m_dwCurTime = GetTickCount();

		if (m_bUseFPS)
		{
			if (m_dwCurTime - m_dwLastTime < 1000 / m_iFPS)
				return;
		}

		m_fElapseTime = (m_dwCurTime - m_dwLastTime) / 1000.0f;
		m_dwLastTime = m_dwCurTime;

		if (m_bPause)
			m_fElapseTime = 0.0f;
	}

	float TimeManager::GetElipseTime()
	{
		return m_fElapseTime * m_fGameSpeed;
	}
}

