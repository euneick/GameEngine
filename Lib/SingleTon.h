#pragma once
#include <Windows.h>

/**
*	@brief		: SingleTon를 제공하는 클래스
*	@details	: 각 Manager의 SingleTon을 담당하는 클래스
*	@author		: Euneick // eternal_sity@naver.com
*	@date		: 2018-10-01
*	@version	: 0.0.1
*/
template < typename T >
class SingleTon
{
private:
	static T * m_pThis;

protected:
	SingleTon()
	{
	}

	virtual ~SingleTon()
	{
	}

public:
	static T * GetInstance()
	{
		if (m_pThis == NULL)
			m_pThis = new T;
		return m_pThis;
	};

	static void DestroyInstance()
	{
		if (m_pThis)
		{
			delete m_pThis;
			m_pThis = NULL;
		}
	};
};

template <typename T> T * SingleTon<T>::m_pThis = 0;