#include "PaperStar.h"
#include "ClientDefines.h"


PaperStar::PaperStar()
{
}


PaperStar::~PaperStar()
{
}

void PaperStar::Init(VECTOR2 _vec2Center)
{
	m_pStarImage = EEObjectManager::GetInstance()->CreateImage("Paper_star.bmp", Z_ORDER_STAR);
	m_pStarImage->SetPosition(_vec2Center);
	m_pStarImage->SetVisibility(false);

	m_pStarLabel = EEObjectManager::GetInstance()->CreateLabel("100", Z_ORDER_STAR);
	_vec2Center.y -= 5;
	m_pStarLabel->SetPosition(_vec2Center);
	m_pStarLabel->SetLabelColor(255, 255, 255);
	m_pStarLabel->SetLabelTextSize(15);
	m_pStarLabel->SetLaelTextBold(true);
	m_pStarLabel->SetVisibility(false);
}

void PaperStar::SetPaperVisibility(bool _b)
{
	m_pStarImage->SetVisibility(_b);
	m_pStarLabel->SetVisibility(_b);
}

void PaperStar::OperChangeScoreLabel(int _iScore)
{
	m_pStarLabel->SetLabelString(std::to_string(_iScore));
}

void PaperStar::Release()
{
}