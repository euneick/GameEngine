#pragma once
#include "GlobalDefines.h"

namespace Euneick
{
	/**
	*	@brief		: Time을 관리하는 클래스
	*	@details	: ElapseTime, FPS를 관리하는 클래스
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
		// TimeManager의 이니셜라이져 함수
		void init(bool _useFPS, int _iFPS);

		// TimeManager의 실시간 호출 함수
		void Update();

		// 현재 frame와 이전 frame의 시간차이(경과시간)를 반환하는 함수
		float GetElipseTime();

		// 현재 게임스피드를 반환하는 함수
		inline float GetGameSpeed()
		{
			return m_fGameSpeed;
		}

		// 게임스피드를 설정하는 함수
		inline void SetGameSpeed(float _fGameSpeed)
		{
			m_fGameSpeed = _fGameSpeed;
		}

		// TimeManager의 일시정지 여부를 설정하는 함수
		inline void SetGamePause(bool _bPause)
		{
			m_bPause = _bPause;
		}

		TimeManager();
		~TimeManager();
	};
}

