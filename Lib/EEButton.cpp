#include "EEButton.h"
#include "ResManager.h"
#include "BitMap.h"


namespace Euneick
{
	EEButton::EEButton()
	{
	}


	EEButton::~EEButton()
	{
	}

	void EEButton::Draw()
	{
		if (!m_bVisibility)
			return;

		m_pBtnBitMap->Draw(m_vec2Position, m_vec2AnchorPoint, m_vec2Scale);
	}

	void EEButton::Release()
	{
	}

	void EEButton::Create(string _strFileName, int _iZOrder)
	{
		m_pBtnBitMap = ResManager::GetInstance()->GetBitMap(_strFileName);

		ResetComponent();
		m_bPause = false;
		m_bVisibility = true;
		m_iZOrder = _iZOrder;

		m_size = m_pBtnBitMap->GetBitMapSize();
		SetObjectRect();
	}
	
	bool EEButton::OnButtonDown(VECTOR2 _vec2Mouse)
	{
		if (m_rcRect.IsVec2InRect(_vec2Mouse))
			return true;

		return false;
	}

	bool EEButton::OnButtonUp(VECTOR2 _vec2Mouse)
	{
		if (m_rcRect.IsVec2InRect(_vec2Mouse))
			return true;

		return false;
	}
}
