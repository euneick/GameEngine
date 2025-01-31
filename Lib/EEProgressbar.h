#pragma once
#include "GlobalDefines.h"
#include "VECTOR2.h"
#include "EEObject.h"

namespace Euneick
{
	enum PROGRESSBAR_STATE
	{
		PROGRESSBAR_STATE_LEFT,
		PROGRESSBAR_STATE_CENTER,
		PROGRESSBAR_STATE_RIGHT,
		PROGRESSBAR_STATE_END
	};

	class BitMap;
	/**
	*	@brief		: ProgressBar를 만들고 제어하는 클래스
	*	@details	: ProgressBar를 만들고 제어하는 클래스, 기본 AnchorPoint(0,0)
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class EEProgressbar : public EEObject
	{
	private:
		BitMap*		m_pProgBarBitMap[PROGRESSBAR_STATE_END];

		VECTOR2		m_vec2BitMapPos;
		SIZE		m_sizeBarBitMap[PROGRESSBAR_STATE_END];

		bool		m_bUseLeftRight;
		float		m_fLength;

		bool		m_bIncreaseAction;
		float		m_fIncreaseActionAmount;
		float		m_fIncreaseActionSpeed;

		bool		m_bDecreaseByTimeAction;
		float		m_fDecreaseByTimeActionTotalTime;
		float		m_fDecreaseByTimeActionTotalLength;

		// 시간경과에 따라 감소하는 액션의 실시간 호출함수
		void UpdateDecreaseByTime(float _fElapseTime);

		// 증가 액션의 실시간 호출함수
		void UpdateIncreaseAction(float _fElapseTime);

	public:
		virtual void Create(string _strFileName, int _iZOrder);
		virtual bool Update(float _fElapaseTime);
		virtual void Draw();
		virtual void Release();

		// ProgressBar의 길이를 설정하는 함수 (왼쪽, 오른쪽 이미지 별도)
		void SetProgressBarLength(float _fLength);

		// ProgressBar의 왼쪽, 오른쪽 이미지를 추가하는 함수
		void AddLeftRightBar(string _strLeftFileName, string _strRightFileName);

		// ProgressBar의 가운데 이미지를 그리는 함수
		void DrawCenterBar();

		// 시간경과에 따라 감소하는 액션을 등록하는 함수
		void SetDecreaseByTime(float _fActionTime);

		// 지정된 속도에 의해 길이가 증가하는 액션을 등록하는 함수
		void SetIncreaseAction(float _fCount, float _fSpeed);

		// IncreaseAction을 멈추는 함수
		void OnIncreaseActionStop();

		// ProgressBar의 현재 길이를 반환하는 함수
		inline float GetBarLength()
		{
			return m_fLength;
		}

		EEProgressbar();
		~EEProgressbar();
	};
}

