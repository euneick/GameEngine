#pragma once
#include "GlobalDefines.h"
#include "VECTOR2.h"
#include "EEObject.h"

namespace Euneick
{
	class BitMap;
	/**
	*	@brief		: BitMap을 Object화 하는 클래스
	*	@details	: BitMap자체에 Position, Rect등 속성을 주어 하나의 Object로 사용하는 클래스
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class EEImage : public EEObject
	{
	private:
		map<int, BitMap*>	m_mapBitMapFrames;
		BitMap*				m_pCurBitMap;

		int			m_iColliderRadius;
		int			m_iFrameTotalCount;

		bool		m_bToggleVisibility;
		bool		m_bToggleVisibiltiyRepeatForever;
		float		m_fToggleVisibilityTotalTime;
		float		m_fToggleVisibilityTimer;
		float		m_fToggleVisibilityDuration;

		bool		m_bAnimate;
		bool		m_bAnimateRepeatForever;
		int			m_iAnimateIndex;
		float		m_fAnimateTotalTime;
		float		m_fAnimateTimer;
		float		m_fAnimateDuration;

		bool		m_bMoveTo;
		VECTOR2		m_vec2MoveTo;
		float		m_fMoveToTimer;
		float		m_fMoveSpeed;

		bool		m_bMoveBy;
		bool		m_bMoveByRepeatForever;
		VECTOR2		m_vec2MoveBy;
		float		m_fMoveByTimer;
		float		m_fMoveByDuration;

		// ToggleVisibility Action의 실시간 호출 함수
		void UpdateToggleVisibility(float _fElapseTime);

		// Animate Action의 실시간 호출 함수
		void UpdateAnimate(float _fElapseTime);

		// MoveTo Action의 실시간 호출 함수
		void UpdateMoveTo(float _fElapseTime);

		// MoveBy Action의 실시간 호출 함수
		void UpdateMoveBy(float _fElapseTime);

	public:
		virtual void Create(string _strFileName, int _iZOrder);
		virtual bool Update(float _fElapaseTime);
		virtual void Draw();
		virtual void Release();

		// Animation Frame을 등록하는 함수
		void RegistBitMapFrame(string _strFileName);

		// 현재 BitMap을 지정 Animation으로 바꾸는 함수
		void SetBitMapFrame(int _iIndex);

		// ToggleVisibility Action 등록 함수
		void SetToggleVisibility(float _fActionTime, float _fDuration);

		// ToggleVisibility 무한반복 Action 등록 함수
		void SetToggleVisibility(float _fDuration);

		// BitMap Frame들의 Animate Action 등록 함수
		void SetAnimate(float _fActionTime, float _fDuration);

		// BitMap Frame들의 Animate 무한반복 Action 등록 함수
		void SetAnimate(float _fDuration);

		// MoveTo Action 등록 함수
		void SetMoveTo(float _fMoveSpeed, VECTOR2 _vec2MoveTo);

		// MoveBy Action 등록 함수
		void SetMoveBy(float _fMoveSpeed, VECTOR2 _vec2MoveBy, float _fMoveByDuration);

		// MoveBy Action 무한지속 등록 함수
		void SetMoveBy(float _fMoveSpeed, VECTOR2 _vec2MoveBy);

		// 원형 충돌 체크
		bool IntersectCircle(VECTOR2 _vec2Target, int _iTargetRadius);

		// 원 충돌체의 반지름을 반환하는 함수
		inline int GetColliderRadius()
		{
			return m_iColliderRadius;
		}

		// 원 충돌체의 반지름을 설정하는 함수
		inline void SetColliderRadius(int _i)
		{
			m_iColliderRadius = _i;
		}

		// MoveTo Action의 실행 여부를 반환하는 함수
		inline bool IsMoveToAction()
		{
			return m_bMoveTo;
		}

		// MoveBy Action의 실행 여부를 반환하는 함수
		inline bool IsMoveByAction()
		{
			return m_bMoveBy;
		}

		EEImage();
		virtual ~EEImage();
	};
}

