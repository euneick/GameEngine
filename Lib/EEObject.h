#pragma once
#include "GlobalDefines.h"
#include "VECTOR2.h"

namespace Euneick
{
	/**
	*	@brief		: Object���� �߻�Ŭ����
	*	@details	: Object���� �߻�Ŭ����
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class EEObject
	{
	protected:
		VECTOR2		m_vec2Position;
		VECTOR2		m_vec2AnchorPoint;
		VECTOR2		m_vec2Scale;

		SIZE		m_size;
		RECT		m_rcRect;
		
		bool		m_bPause;
		bool		m_bVisibility;
		int			m_iZOrder;

		// Object�� Rect�� �����ϴ� �Լ�
		void SetObjectRect();

	public:
		// Object�� �����ϴ� ���� �����Լ�
		virtual void Create(string _strFileName, int _iZOrder) = 0;

		// Object�� �ǽð� ȣ���ϴ� ���� �����Լ�
		virtual bool Update(float _fElapaseTime) = 0;

		// Object�� �׸��� ���� �����Լ�
		virtual void Draw() = 0;

		// Object�� �޸� ���� ���� �����Լ�
		virtual void Release() = 0;

		// Position, AnchorPoint, Scale���� �⺻������ �����ϴ� �Լ�
		void ResetComponent();

		// Object�� AnchorPoint�� �����ϴ� �Լ�
		void SetAnchorPoint(VECTOR2 _vec2);

		// Object�� AnchorPoint�� ��ȯ�ϴ� �Լ�
		VECTOR2 GetAnchorPoint();

		// Object�� Position�� �����ϴ� �Լ�
		void SetPosition(VECTOR2 _vec2);

		// Object�� Position�� ��ȯ�ϴ� �Լ�
		VECTOR2	GetPosition();

		// Object�� Scale�� �����ϴ� �Լ�
		void SetScale(VECTOR2 _vec2);

		// Object�� Scale�� ��ȯ�ϴ� �Լ�
		VECTOR2 GetScale();

		// Object�� Size�� ��ȯ�ϴ� �Լ�
		inline SIZE GetObjectSize()
		{
			return m_size;
		}

		// Object�� Visibility ���¸� ��ȯ�ϴ� �Լ�
		inline bool GetVisibility()
		{
			return m_bVisibility;
		}

		// Object�� Visibility ���¸� �����ϴ� �Լ�
		inline void SetVisibility(bool _b)
		{
			m_bVisibility = _b;
		}

		// Objectdml ZOrder�� ��ȯ�ϴ� �Լ�
		inline int GetZOrder()
		{
			return m_iZOrder;
		}

		// Object�� ZOrder�� �����ϴ� �Լ�
		void SetZOrder(int _iZOrder);

		// Object�� Euneick::RECT�� ��ȯ�ϴ� �Լ�
		inline RECT GetObjectRect()
		{
			return m_rcRect;
		}

		EEObject();
		virtual ~EEObject();
	};
}

