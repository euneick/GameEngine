#include "EEProgressbar.h"
#include "ResManager.h"
#include "BitMap.h"

namespace Euneick
{
	EEProgressbar::EEProgressbar()
	{
	}


	EEProgressbar::~EEProgressbar()
	{
	}

	void EEProgressbar::Create(string _strFileName, int _iZOrder)
	{
		m_pProgBarBitMap[PROGRESSBAR_STATE_CENTER] = ResManager::GetInstance()->GetBitMap(_strFileName);

		ResetComponent();
		m_bPause = false;
		m_bVisibility = true;
		m_bUseLeftRight = false;
		m_iZOrder = _iZOrder;
		m_fLength = 0.0f;

		m_bIncreaseAction = false;
		m_fIncreaseActionAmount = 0.0f;
		m_fIncreaseActionSpeed = 0.0f;

		m_bDecreaseByTimeAction = false;
		m_fDecreaseByTimeActionTotalTime = 0.0f;
		m_fDecreaseByTimeActionTotalLength = 0.0f;

		m_vec2AnchorPoint = VECTOR2(0.0f, 0.0f);
		m_vec2BitMapPos = VECTOR2(0, 0);

		m_size = m_pProgBarBitMap[PROGRESSBAR_STATE_CENTER]->GetBitMapSize();
		m_sizeBarBitMap[PROGRESSBAR_STATE_CENTER] = m_pProgBarBitMap[PROGRESSBAR_STATE_CENTER]->GetBitMapSize();
		SetObjectRect();
	}

	void EEProgressbar::AddLeftRightBar(string _strLeftFileName, string _strRightFileName)
	{
		m_pProgBarBitMap[PROGRESSBAR_STATE_LEFT] = ResManager::GetInstance()->GetBitMap(_strLeftFileName);
		m_pProgBarBitMap[PROGRESSBAR_STATE_RIGHT] = ResManager::GetInstance()->GetBitMap(_strRightFileName);

		m_sizeBarBitMap[PROGRESSBAR_STATE_LEFT] = m_pProgBarBitMap[PROGRESSBAR_STATE_LEFT]->GetBitMapSize();
		m_sizeBarBitMap[PROGRESSBAR_STATE_RIGHT] = m_pProgBarBitMap[PROGRESSBAR_STATE_RIGHT]->GetBitMapSize();

		m_bUseLeftRight = true;
	}

	void EEProgressbar::SetProgressBarLength(float _fLength)
	{
		m_fLength = _fLength;
	}

	bool EEProgressbar::Update(float _fElapaseTime)
	{
		if (m_bPause)
			return false;

		if (m_bDecreaseByTimeAction)
			UpdateDecreaseByTime(_fElapaseTime);

		if (m_bIncreaseAction)
			UpdateIncreaseAction(_fElapaseTime);

		return false;
	}

	void EEProgressbar::UpdateDecreaseByTime(float _fElapseTime)
	{
		if (m_fLength <= 0.0f)
		{
			m_fLength = 0.0f;
			m_bDecreaseByTimeAction = false;

			return;
		}

		m_fLength -= (m_fDecreaseByTimeActionTotalLength / m_fDecreaseByTimeActionTotalTime) * _fElapseTime;
	}

	void EEProgressbar::UpdateIncreaseAction(float _fElapseTime)
	{
		m_fLength += m_fIncreaseActionSpeed * _fElapseTime;

		m_fIncreaseActionAmount -= m_fIncreaseActionSpeed * _fElapseTime;;

		if (m_fIncreaseActionAmount <= 0)
		{
			m_fIncreaseActionAmount = 0;
			m_bIncreaseAction = false;
		}
	}

	void EEProgressbar::Draw()
	{
		if (!m_bVisibility)
			return;

		m_vec2BitMapPos = m_vec2Position;

		if (m_bUseLeftRight)
		{
			m_pProgBarBitMap[PROGRESSBAR_STATE_LEFT]->Draw(m_vec2BitMapPos, m_vec2AnchorPoint, m_vec2Scale);
			m_vec2BitMapPos.x += m_sizeBarBitMap[PROGRESSBAR_STATE_LEFT].cx;
			DrawCenterBar();
			m_pProgBarBitMap[PROGRESSBAR_STATE_RIGHT]->Draw(m_vec2BitMapPos, m_vec2AnchorPoint, m_vec2Scale);
		}
		else
			DrawCenterBar();
	}

	void EEProgressbar::DrawCenterBar()
	{
		for (int i = 0; i < (int)m_fLength; i++)
		{
			m_pProgBarBitMap[PROGRESSBAR_STATE_CENTER]->Draw(m_vec2BitMapPos, m_vec2AnchorPoint, m_vec2Scale);
			m_vec2BitMapPos.x += m_sizeBarBitMap[PROGRESSBAR_STATE_CENTER].cx;
		}
	}

	void EEProgressbar::SetDecreaseByTime(float _fActionTime)
	{
		m_bDecreaseByTimeAction = true;
		m_fDecreaseByTimeActionTotalTime = _fActionTime;
		m_fDecreaseByTimeActionTotalLength = m_fLength;
	}


	void EEProgressbar::SetIncreaseAction(float _fAmount, float _fSpeed)
	{
		m_bIncreaseAction = true;
		m_fIncreaseActionAmount += _fAmount;
		m_fIncreaseActionSpeed = _fSpeed;
	}

	void EEProgressbar::OnIncreaseActionStop()
	{
		m_bIncreaseAction = false;
		m_fIncreaseActionAmount = 0;
		m_fIncreaseActionSpeed = 0;
	}

	void EEProgressbar::Release()
	{
	}
}
