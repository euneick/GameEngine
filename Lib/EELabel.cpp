#include "EELabel.h"
#include "ResManager.h"


namespace Euneick
{
	EELabel::EELabel()
	{
	}


	EELabel::~EELabel()
	{
	}

	void EELabel::Draw()
	{
		if (!m_bVisibility)
			return;

		SetTextColor(ResManager::GetInstance()->GetBackBufDC(), RGB(m_rgb.r, m_rgb.g, m_rgb.b));
		SetTextAlign(ResManager::GetInstance()->GetBackBufDC(), m_uiAlign);

		HFONT font, oldfont;
		font = CreateFont(m_iTextSize, 0, 0, 0, ((int)m_bTextBold * 1000), 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "µ¸¿ò");
		oldfont = (HFONT)SelectObject(ResManager::GetInstance()->GetBackBufDC(), font);
		TextOut(ResManager::GetInstance()->GetBackBufDC(), (int)m_vec2Position.x, (int)m_vec2Position.y, m_strText.c_str(), m_strText.length());
		SelectObject(ResManager::GetInstance()->GetBackBufDC(), oldfont);
		DeleteObject(font);
	}

	void EELabel::Release()
	{
	}

	void EELabel::Create(string _strText, int _iZOrder)
	{
		ResetComponent();
		m_rgb = EERGB(0, 0, 0);

		m_bPause = false;
		m_bVisibility = true;
		m_bTextBold = false;
		m_iTextSize = 10;
		m_iZOrder = _iZOrder;
		m_uiAlign = TA_CENTER;

		SetObjectRect();

		m_strText = _strText;

		m_bMoveBy = false;
		m_bMoveByRepeatForever = false;
		m_vec2MoveBy = VECTOR2(0, 0);
		m_fMoveSpeed = 0.0f;
		m_fMoveByTimer = 0.0f;
		m_fMoveByDuration = 0.0f;
	}

	bool EELabel::Update(float _fElapseTime)
	{
		if (m_bMoveBy)
			UpdateMoveBy(_fElapseTime);

		return false;
	}

	void EELabel::UpdateMoveBy(float _fElapseTime)
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

	void EELabel::SetLabelString(string _str)
	{
		m_strText = _str;
	}

	void EELabel::SetLabelColor(int r, int g, int b)
	{
		m_rgb = EERGB(r, g, b);
	}

	void EELabel::SetLabelAlignment(ALIGNMENT _e)
	{
		switch (_e)
		{
		case Euneick::ALIGNMENT_LEFT:
			m_uiAlign = TA_LEFT;
			break;
		case Euneick::ALIGNMENT_CENTER:
			m_uiAlign = TA_CENTER;
			break;
		case Euneick::ALIGNMENT_RIGHT:
			m_uiAlign = TA_RIGHT;
			break;
		}
	}

	void EELabel::SetMoveBy(float _fMoveSpeed, VECTOR2 _vec2MoveBy, float _fMoveByDuration)
	{
		m_bMoveBy = true;
		m_bMoveByRepeatForever = false;
		m_fMoveSpeed = _fMoveSpeed;
		m_vec2MoveBy = _vec2MoveBy;
		m_fMoveByDuration = _fMoveByDuration;
	}

	void EELabel::SetMoveBy(float _fMoveSpeed, VECTOR2 _vec2MoveBy)
	{
		m_bMoveBy = true;
		m_bMoveByRepeatForever = true;
		m_fMoveSpeed = _fMoveSpeed;
		m_vec2MoveBy = _vec2MoveBy;
	}

}
