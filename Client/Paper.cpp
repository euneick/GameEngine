#include "Paper.h"
#include "ClientDefines.h"

VECTOR2 m_vec2PaperPos[PAPER_STATE_END] = { {66,382},{341,381},{203,231},{204,542} };

Paper::Paper()
{
}


Paper::~Paper()
{
}

void Paper::Init(VECTOR2 _vec2Center)
{
	m_pPaperImage = EEObjectManager::GetInstance()->CreateImage("Paper_0.bmp", Z_ORDER_PAPER_BACK);
	for (int i = 1; i < PAPER_STATE_END; i++)
		m_pPaperImage->RegistBitMapFrame("Paper_" + std::to_string(i) + ".bmp");
	int _iRand = rand() % (int)PAPER_STATE_END;
	
	m_vec2Center = _vec2Center;

	m_ePaperState = (PAPER_STATE)_iRand;

	m_pPaperImage->SetBitMapFrame(_iRand);
	m_pPaperImage->SetPosition(_vec2Center);
}

void Paper::Update(float _fElapseTime)
{
	if (m_pPaperImage->GetPosition() == m_vec2PaperPos[(int)m_ePaperState])
	{
		m_pPaperImage->SetZOrder(Z_ORDER_PAPER_BACK);
		SetPaperCenter();
	}
}

void Paper::OperCorrectAction()
{
	m_pPaperImage->SetZOrder(Z_ORDER_PAPER_ACTION);
	m_pPaperImage->SetMoveTo(1000.0f, m_vec2PaperPos[(int)m_ePaperState]);
}

void Paper::OperWrongAction()
{
}

void Paper::SetPaperCenter()
{
	m_pPaperImage->SetPosition(m_vec2Center);

	int _iRand = rand() % (int)PAPER_STATE_END;
	m_ePaperState = (PAPER_STATE)_iRand;
	m_pPaperImage->SetBitMapFrame(_iRand);
}

void Paper::SetPaperZOrder(int _iZOrder)
{
	m_pPaperImage->SetZOrder(_iZOrder);
}

void Paper::Release()
{
}
