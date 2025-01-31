#pragma once
#include "GlobalDefines.h"

namespace Euneick
{
	/**
	*	@brief		: Time�� �����ϴ� Ŭ����
	*	@details	: ElapseTime, FPS�� �����ϴ� Ŭ����
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class TimeManager : public SingleTon<TimeManager>
	{
	private:
		bool		m_bPause;
		bool		m_bUseFPS;
		int			m_iFPS;

		DWORD		m_dwLastTime;
		DWORD		m_dwCurTime;
		float		m_fElapseTime;
		float		m_fGameSpeed;

	public:
		// TimeManager�� �̴ϼȶ����� �Լ�
		void init(bool _useFPS, int _iFPS);

		// TimeManager�� �ǽð� ȣ�� �Լ�
		void Update();

		// ���� frame�� ���� frame�� �ð�����(����ð�)�� ��ȯ�ϴ� �Լ�
		float GetElipseTime();

		// ���� ���ӽ��ǵ带 ��ȯ�ϴ� �Լ�
		inline float GetGameSpeed()
		{
			return m_fGameSpeed;
		}

		// ���ӽ��ǵ带 �����ϴ� �Լ�
		inline void SetGameSpeed(float _fGameSpeed)
		{
			m_fGameSpeed = _fGameSpeed;
		}

		// TimeManager�� �Ͻ����� ���θ� �����ϴ� �Լ�
		inline void SetGamePause(bool _bPause)
		{
			m_bPause = _bPause;
		}

		TimeManager();
		~TimeManager();
	};
}

