#pragma once
#include "GlobalDefines.h"
#include "VECTOR2.h"
#include "EEObject.h"

namespace Euneick
{
	class BitMap;
	/**
	*	@brief		: BitMap�� Objectȭ �ϴ� Ŭ����
	*	@details	: BitMap��ü�� Position, Rect�� �Ӽ��� �־� �ϳ��� Object�� ����ϴ� Ŭ����
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

		// ToggleVisibility Action�� �ǽð� ȣ�� �Լ�
		void UpdateToggleVisibility(float _fElapseTime);

		// Animate Action�� �ǽð� ȣ�� �Լ�
		void UpdateAnimate(float _fElapseTime);

		// MoveTo Action�� �ǽð� ȣ�� �Լ�
		void UpdateMoveTo(float _fElapseTime);

		// MoveBy Action�� �ǽð� ȣ�� �Լ�
		void UpdateMoveBy(float _fElapseTime);

	public:
		virtual void Create(string _strFileName, int _iZOrder);
		virtual bool Update(float _fElapaseTime);
		virtual void Draw();
		virtual void Release();

		// Animation Frame�� ����ϴ� �Լ�
		void RegistBitMapFrame(string _strFileName);

		// ���� BitMap�� ���� Animation���� �ٲٴ� �Լ�
		void SetBitMapFrame(int _iIndex);

		// ToggleVisibility Action ��� �Լ�
		void SetToggleVisibility(float _fActionTime, float _fDuration);

		// ToggleVisibility ���ѹݺ� Action ��� �Լ�
		void SetToggleVisibility(float _fDuration);

		// BitMap Frame���� Animate Action ��� �Լ�
		void SetAnimate(float _fActionTime, float _fDuration);

		// BitMap Frame���� Animate ���ѹݺ� Action ��� �Լ�
		void SetAnimate(float _fDuration);

		// MoveTo Action ��� �Լ�
		void SetMoveTo(float _fMoveSpeed, VECTOR2 _vec2MoveTo);

		// MoveBy Action ��� �Լ�
		void SetMoveBy(float _fMoveSpeed, VECTOR2 _vec2MoveBy, float _fMoveByDuration);

		// MoveBy Action �������� ��� �Լ�
		void SetMoveBy(float _fMoveSpeed, VECTOR2 _vec2MoveBy);

		// ���� �浹 üũ
		bool IntersectCircle(VECTOR2 _vec2Target, int _iTargetRadius);

		// �� �浹ü�� �������� ��ȯ�ϴ� �Լ�
		inline int GetColliderRadius()
		{
			return m_iColliderRadius;
		}

		// �� �浹ü�� �������� �����ϴ� �Լ�
		inline void SetColliderRadius(int _i)
		{
			m_iColliderRadius = _i;
		}

		// MoveTo Action�� ���� ���θ� ��ȯ�ϴ� �Լ�
		inline bool IsMoveToAction()
		{
			return m_bMoveTo;
		}

		// MoveBy Action�� ���� ���θ� ��ȯ�ϴ� �Լ�
		inline bool IsMoveByAction()
		{
			return m_bMoveBy;
		}

		EEImage();
		virtual ~EEImage();
	};
}

