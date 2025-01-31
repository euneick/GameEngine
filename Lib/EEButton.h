#pragma once
#include "GlobalDefines.h"
#include "VECTOR2.h"
#include "EEObject.h"

namespace Euneick
{
	class BitMap;
	/**
	*	@brief		: Button을 만들고 제어하는 클래스
	*	@details	: Button을 만들고 제어하는 클래스
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class EEButton : public EEObject
	{
	private:
		BitMap*		m_pBtnBitMap;

	public:
		virtual void Create(string _strFileName, int _iZOrder);
		virtual bool Update(float _fElapaseTime) { return false; }
		virtual void Draw();
		virtual void Release();

		// Button의 Mouse Down 이벤트
		bool OnButtonDown(VECTOR2 _vec2Mouse);

		// Button의 Mouse Up 이벤트
		bool OnButtonUp(VECTOR2 _vec2Mouse);

		EEButton();
		virtual ~EEButton();
	};
}

