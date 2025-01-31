#pragma once
#include "GlobalDefines.h"
#include "VECTOR2.h"

namespace Euneick
{
	/**
	*	@brief		: Object들의 추상클래스
	*	@details	: Object들의 추상클래스
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

		// Object의 Rect를 정의하는 함수
		void SetObjectRect();

	public:
		// Object를 생성하는 순수 가상함수
		virtual void Create(string _strFileName, int _iZOrder) = 0;

		// Object의 실시간 호출하는 순수 가상함수
		virtual bool Update(float _fElapaseTime) = 0;

		// Object를 그리는 순수 가상함수
		virtual void Draw() = 0;

		// Object의 메모리 해제 순수 가상함수
		virtual void Release() = 0;

		// Position, AnchorPoint, Scale값을 기본값으로 설정하는 함수
		void ResetComponent();

		// Object의 AnchorPoint를 설정하는 함수
		void SetAnchorPoint(VECTOR2 _vec2);

		// Object의 AnchorPoint를 반환하는 함수
		VECTOR2 GetAnchorPoint();

		// Object의 Position를 설정하는 함수
		void SetPosition(VECTOR2 _vec2);

		// Object의 Position를 반환하는 함수
		VECTOR2	GetPosition();

		// Object의 Scale을 설정하는 함수
		void SetScale(VECTOR2 _vec2);

		// Object의 Scale을 반환하는 함수
		VECTOR2 GetScale();

		// Object의 Size를 반환하는 함수
		inline SIZE GetObjectSize()
		{
			return m_size;
		}

		// Object의 Visibility 상태를 반환하는 함수
		inline bool GetVisibility()
		{
			return m_bVisibility;
		}

		// Object의 Visibility 상태를 설정하는 함수
		inline void SetVisibility(bool _b)
		{
			m_bVisibility = _b;
		}

		// Objectdml ZOrder를 반환하는 함수
		inline int GetZOrder()
		{
			return m_iZOrder;
		}

		// Object의 ZOrder를 설정하는 함수
		void SetZOrder(int _iZOrder);

		// Object의 Euneick::RECT를 반환하는 함수
		inline RECT GetObjectRect()
		{
			return m_rcRect;
		}

		EEObject();
		virtual ~EEObject();
	};
}

