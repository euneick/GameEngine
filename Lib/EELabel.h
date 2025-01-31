#pragma once
#include "EEObject.h"

namespace Euneick
{
	enum ALIGNMENT
	{
		ALIGNMENT_LEFT,
		ALIGNMENT_CENTER,
		ALIGNMENT_RIGHT,
		ALIGNMENT_END
	};

	/**
	*	@brief		: Label을 만드는 클래스
	*	@details	: Label을 만들고 String을 그리는 클래스
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class EELabel : public EEObject
	{
	private:
		DWORD		m_dwDrawOption;
		string		m_strText;
		EERGB		m_rgb;

		bool		m_bTextBold;
		int			m_iTextSize;
		UINT		m_uiAlign;

		bool		m_bMoveBy;
		bool		m_bMoveByRepeatForever;
		VECTOR2		m_vec2MoveBy;
		float		m_fMoveSpeed;
		float		m_fMoveByTimer;
		float		m_fMoveByDuration;

		// MoveBy Action의 실시간 호출 함수
		void UpdateMoveBy(float _fElapseTime);

	public:
		virtual void Create(string _strFileName, int _iZOrder);
		virtual bool Update(float _fElapseTime);
		virtual void Draw();
		virtual void Release();

		// Label의 String을 설정하는 함수
		void SetLabelString(string _str);

		// Label의 색상을 설정하는 함수
		void SetLabelColor(int r, int g, int b);

		// Label의 Text 크기를 설정하는 함수
		inline void SetLabelTextSize(int _iSize)
		{
			m_iTextSize = _iSize;
		}

		// Label의 Text 굵기를 설정하는 함수
		inline void SetLaelTextBold(bool _bBold)
		{
			m_bTextBold = _bBold;
		}

		// Label의 Text 정렬방식을 설정하는 함수
		void SetLabelAlignment(ALIGNMENT _e);

		// MoveBy Action 등록 함수
		void SetMoveBy(float _fMoveSpeed, VECTOR2 _vec2MoveBy, float _fMoveByDuration);

		// MoveBy Action 무한지속 등록 함수
		void SetMoveBy(float _fMoveSpeed, VECTOR2 _vec2MoveBy);

		EELabel();
		virtual ~EELabel();
	};
}
