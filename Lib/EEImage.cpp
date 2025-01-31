#include "EEImage.h"
#include "ResManager.h"
#include "BitMap.h"


namespace Euneick
{
	EEImage::EEImage()
	{
	}


	EEImage::~EEImage()
	{
	}

	void EEImage::Create(string _strFileName, int _iZOrder)
	{
		m_iFrameTotalCount = 0;
		m_iZOrder = _iZOrder;

		m_pCurBitMap = ResManager::GetInstance()->GetBitMap(_strFileName);
		m_mapBitMapFrames.insert(make_pair(m_iFrameTotalCount, m_pCurBitMap));
		m_iFrameTotalCount++;

		ResetComponent();
		m_bPause = false;
		m_bVisibility = true;

		m_bToggleVisibility = false;
		m_bToggleVisibiltiyRepeatForever = false;
		m_fToggleVisibilityTotalTime = 0.0f;
		m_fToggleVisibilityTimer = 0.0f;
		m_fToggleVisibilityDuration = 0.0f;

		m_bAnimate = false;
		m_bAnimateRepeatForever = false;
		m_iAnimateIndex = 0;
		m_fAnimateTotalTime = 0.0f;
		m_fAnimateTimer = 0.0f;
		m_fAnimateDuration = 0.0f;

		m_bMoveTo = false;
		m_vec2MoveTo = VECTOR2(0, 0);
		m_fMoveToTimer = 0.0f;
		m_fMoveSpeed = 0.0f;

		m_bMoveBy = false;
		m_bMoveByRepeatForever = false;
		m_vec2MoveBy = VECTOR2(0, 0);
		m_fMoveByTimer = 0.0f;
		m_fMoveByDuration = 0.0f;

		m_size = m_pCurBitMap->GetBitMapSize();
		SetObjectRect();
	}

	void EEImage::RegistBitMapFrame(string _strFileName)
	{
		BitMap* _pNew = ResManager::GetInstance()->GetBitMap(_strFileName);
		m_mapBitMapFrames.insert(make_pair(m_iFrameTotalCount, _pNew));
		m_iFrameTotalCount++;
	}

	void EEImage::SetBitMapFrame(int _iIndex)
	{
		auto iter = m_mapBitMapFrames.find(_iIndex);

		if (iter == m_mapBitMapFrames.end())
		{
			assert(!("BitMapFrame is not exist"));
			return;
		}

		m_pCurBitMap = iter->second;
		m_size = m_pCurBitMap->GetBitMapSize();
	}

	bool EEImage::Update(float _fElapseTime)
	{
		if (m_bPause)
			return false;

		if (m_bToggleVisibility)
			UpdateToggleVisibility(_fElapseTime);

		if (m_bAnimate)
			UpdateAnimate(_fElapseTime);

		if (m_bMoveTo)
			UpdateMoveTo(_fElapseTime);

		if (m_bMoveBy)
			UpdateMoveBy(_fElapseTime);

		return false;
	}

	void EEImage::UpdateToggleVisibility(float _fElapseTime)
	{
		m_fToggleVisibilityTimer += _fElapseTime;

		if (m_fToggleVisibilityTimer >= m_fToggleVisibilityDuration)
		{
			m_fToggleVisibilityTimer = 0.0f;

			m_bVisibility = !m_bVisibility;
		}

		if (!m_bToggleVisibiltiyRepeatForever)
		{
			m_fToggleVisibilityTotalTime -= _fElapseTime;

			if (m_fToggleVisibilityTotalTime <= 0.0f)
			{
				m_bToggleVisibility = false;
				m_bToggleVisibiltiyRepeatForever = false;
				m_fToggleVisibilityTotalTime = 0.0f;
				m_fToggleVisibilityTimer = 0.0f;
				m_fToggleVisibilityDuration = 0.0f;
			}
		}
	}

	void EEImage::UpdateAnimate(float _fElapseTime)
	{
		m_fAnimateTimer += _fElapseTime;

		if (m_fAnimateTimer >= m_fAnimateDuration)
		{
			m_fAnimateTimer = 0.0f;
			m_iAnimateIndex++;
			if (m_iAnimateIndex >= m_mapBitMapFrames.size())
				m_iAnimateIndex = 0;

			SetBitMapFrame(m_iAnimateIndex);
		}

		if (!m_bAnimateRepeatForever)
		{
			m_fAnimateTotalTime -= _fElapseTime;

			if (m_fAnimateTotalTime <= 0.0f)
			{
				m_bAnimate = false;
				m_bAnimateRepeatForever = false;
				m_iAnimateIndex = 0;
				m_fAnimateTotalTime = 0.0f;
				m_fAnimateTimer = 0.0f;
				m_fAnimateDuration = 0.0f;
			}
		}
	}

	void EEImage::UpdateMoveTo(float _fElapseTime)
	{
		m_fMoveToTimer += _fElapseTime;

		VECTOR2 _vec2 = VECTOR2(m_vec2MoveTo.x - m_vec2Position.x, m_vec2MoveTo.y - m_vec2Position.y);
		_vec2.Normalize();

		bool _bOperX = false;
		if (m_vec2MoveTo.x >= m_vec2Position.x && m_vec2Position.x + (_vec2.x * m_fMoveSpeed * _fElapseTime) >= m_vec2MoveTo.x ||
			m_vec2MoveTo.x <= m_vec2Position.x && m_vec2Position.x + (_vec2.x * m_fMoveSpeed * _fElapseTime) <= m_vec2MoveTo.x)
		{
			_bOperX = true;
			m_vec2Position.x = m_vec2MoveTo.x;
		}
		else
		{
			m_vec2Position.x += _vec2.x * m_fMoveSpeed * _fElapseTime;
		}

		bool _bOperY = false;
		if (m_vec2MoveTo.y >= m_vec2Position.y && m_vec2Position.y + (_vec2.y * m_fMoveSpeed * _fElapseTime) >= m_vec2MoveTo.y ||
			m_vec2MoveTo.y <= m_vec2Position.y && m_vec2Position.y + (_vec2.y * m_fMoveSpeed * _fElapseTime) <= m_vec2MoveTo.y)
		{
			_bOperY = true;
			m_vec2Position.y = m_vec2MoveTo.y;
		}
		else
		{
			m_vec2Position.y += _vec2.y * m_fMoveSpeed * _fElapseTime;
		}

		if (_bOperX && _bOperY)
			m_bMoveTo = false;
	}

	void EEImage::UpdateMoveBy(float _fElapseTime)
	{
		m_fMoveByTimer += _fElapseTime;
		
		m_vec2Position.x += m_vec2MoveBy.x * m_fMoveSpeed * _fElapseTime;
		m_vec2Position.y += m_vec2MoveBy.y * m_fMoveSpeed * _fElapseTime;

		if (!m_bMoveByRepeatForever)
		{
			if (m_fMoveByTimer >= m_fMoveByDuration)
			{
				m_bMoveBy = false;
				m_vec2MoveBy = VECTOR2(0, 0);
				m_fMoveByTimer = 0.0f;
				m_fMoveByDuration = 0.0f;

				return;
			}
		}
	}

	void EEImage::Draw()
	{
		if (!m_bVisibility)
			return;

		m_pCurBitMap->Draw(m_vec2Position, m_vec2AnchorPoint, m_vec2Scale);
	}

	void EEImage::Release()
	{
		m_mapBitMapFrames.clear();
	}

	void EEImage::SetToggleVisibility(float _fActionTime, float _fDuration)
	{
		m_bToggleVisibility = true;
		m_bToggleVisibiltiyRepeatForever = false;
		m_fToggleVisibilityTotalTime = _fActionTime;
		m_fToggleVisibilityDuration = _fDuration;
	}

	void EEImage::SetToggleVisibility(float _fDuration)
	{
		m_bToggleVisibility = true;
		m_bToggleVisibiltiyRepeatForever = true;
		m_fToggleVisibilityDuration = _fDuration;
	}

	void EEImage::SetAnimate(float _fActionTime, float _fDuration)
	{
		m_bAnimate = true;
		m_bAnimateRepeatForever = false;
		m_fAnimateTotalTime = _fActionTime;
		m_fAnimateDuration = _fDuration;
	}

	void EEImage::SetAnimate(float _fDuration)
	{
		m_bAnimate = true;
		m_bAnimateRepeatForever = true;
		m_fAnimateDuration = _fDuration;
	}

	void EEImage::SetMoveTo(float _fMoveSpeed, VECTOR2 _vec2MoveTo)
	{
		m_bMoveTo = true;
		m_fMoveSpeed = _fMoveSpeed;
		m_vec2MoveTo = _vec2MoveTo;
	}

	void EEImage::SetMoveBy(float _fMoveSpeed, VECTOR2 _vec2MoveBy, float _fMoveByDuration)
	{
		m_bMoveBy = true;
		m_bMoveByRepeatForever = false;
		m_fMoveSpeed = _fMoveSpeed;
		m_vec2MoveBy = _vec2MoveBy;
		m_fMoveByDuration = _fMoveByDuration;
	}

	void EEImage::SetMoveBy(float _fMoveSpeed, VECTOR2 _vec2MoveBy)
	{
		m_bMoveBy = true;
		m_bMoveByRepeatForever = true;
		m_fMoveSpeed = _fMoveSpeed;
		m_vec2MoveBy = _vec2MoveBy;
	}

	bool EEImage::IntersectCircle(VECTOR2 _vec2Target, int _iTargetRadius)
	{
		int _iDistance = sqrt(pow(_vec2Target.x - m_vec2Position.x, 2) + pow(_vec2Target.y - m_vec2Position.y, 2));

		if (_iDistance <= m_iColliderRadius + _iTargetRadius)
			return true;

		return false;
	}
}

