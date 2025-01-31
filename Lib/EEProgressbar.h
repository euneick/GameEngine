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
	*	@brief		: ProgressBar�� ����� �����ϴ� Ŭ����
	*	@details	: ProgressBar�� ����� �����ϴ� Ŭ����, �⺻ AnchorPoint(0,0)
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

		// �ð������ ���� �����ϴ� �׼��� �ǽð� ȣ���Լ�
		void UpdateDecreaseByTime(float _fElapseTime);

		// ���� �׼��� �ǽð� ȣ���Լ�
		void UpdateIncreaseAction(float _fElapseTime);

	public:
		virtual void Create(string _strFileName, int _iZOrder);
		virtual bool Update(float _fElapaseTime);
		virtual void Draw();
		virtual void Release();

		// ProgressBar�� ���̸� �����ϴ� �Լ� (����, ������ �̹��� ����)
		void SetProgressBarLength(float _fLength);

		// ProgressBar�� ����, ������ �̹����� �߰��ϴ� �Լ�
		void AddLeftRightBar(string _strLeftFileName, string _strRightFileName);

		// ProgressBar�� ��� �̹����� �׸��� �Լ�
		void DrawCenterBar();

		// �ð������ ���� �����ϴ� �׼��� ����ϴ� �Լ�
		void SetDecreaseByTime(float _fActionTime);

		// ������ �ӵ��� ���� ���̰� �����ϴ� �׼��� ����ϴ� �Լ�
		void SetIncreaseAction(float _fCount, float _fSpeed);

		// IncreaseAction�� ���ߴ� �Լ�
		void OnIncreaseActionStop();

		// ProgressBar�� ���� ���̸� ��ȯ�ϴ� �Լ�
		inline float GetBarLength()
		{
			return m_fLength;
		}

		EEProgressbar();
		~EEProgressbar();
	};
}

