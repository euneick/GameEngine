#pragma once
#include "GlobalDefines.h"
#include "VECTOR2.h"
#include "EEObject.h"

namespace Euneick
{
	class BitMap;
	/**
	*	@brief		: Button�� ����� �����ϴ� Ŭ����
	*	@details	: Button�� ����� �����ϴ� Ŭ����
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

		// Button�� Mouse Down �̺�Ʈ
		bool OnButtonDown(VECTOR2 _vec2Mouse);

		// Button�� Mouse Up �̺�Ʈ
		bool OnButtonUp(VECTOR2 _vec2Mouse);

		EEButton();
		virtual ~EEButton();
	};
}

