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
	*	@brief		: Label�� ����� Ŭ����
	*	@details	: Label�� ����� String�� �׸��� Ŭ����
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

		// MoveBy Action�� �ǽð� ȣ�� �Լ�
		void UpdateMoveBy(float _fElapseTime);

	public:
		virtual void Create(string _strFileName, int _iZOrder);
		virtual bool Update(float _fElapseTime);
		virtual void Draw();
		virtual void Release();

		// Label�� String�� �����ϴ� �Լ�
		void SetLabelString(string _str);

		// Label�� ������ �����ϴ� �Լ�
		void SetLabelColor(int r, int g, int b);

		// Label�� Text ũ�⸦ �����ϴ� �Լ�
		inline void SetLabelTextSize(int _iSize)
		{
			m_iTextSize = _iSize;
		}

		// Label�� Text ���⸦ �����ϴ� �Լ�
		inline void SetLaelTextBold(bool _bBold)
		{
			m_bTextBold = _bBold;
		}

		// Label�� Text ���Ĺ���� �����ϴ� �Լ�
		void SetLabelAlignment(ALIGNMENT _e);

		// MoveBy Action ��� �Լ�
		void SetMoveBy(float _fMoveSpeed, VECTOR2 _vec2MoveBy, float _fMoveByDuration);

		// MoveBy Action �������� ��� �Լ�
		void SetMoveBy(float _fMoveSpeed, VECTOR2 _vec2MoveBy);

		EELabel();
		virtual ~EELabel();
	};
}
