#include "AirPlaneStar.h"
#include "ClientDefines.h"
#include "AirPlane.h"


AirPlaneStar::AirPlaneStar()
{
}


AirPlaneStar::~AirPlaneStar()
{
}

void AirPlaneStar::Init(AirPlane* _pAirPlane)
{
	m_pAirPlane = _pAirPlane;

	m_pStar = EEObjectManager::GetInstance()->CreateImage("Airplane_star.bmp", Z_ORDER_STAR);
	m_pStar->SetVisibility(false);

	m_pLabel = EEObjectManager::GetInstance()->CreateLabel(std::to_string(0), Z_ORDER_STAR);
	m_pLabel->SetVisibility(false);
	m_pLabel->SetLabelColor(255, 255, 255);
	m_pLabel->SetLabelTextSize(15);
	m_pLabel->SetLaelTextBold(true);

	m_size = m_pStar->GetObjectSize();

	m_pStar->SetColliderRadius(m_size.cx / 2);

	m_eRespawnPos = STAR_RESPAWN_POS_END;
	m_bUse = false;
	m_fMoveSpeed = false;
}

void AirPlaneStar::SetStarPos(bool _bFeverMode)
{
	int _iRespawnPos = rand() % 4;
	m_eRespawnPos = (STAR_RESPAWN_POS)_iRespawnPos;
	if (_bFeverMode)
		m_fMoveSpeed = (rand() % 20) + 50;
	else
		m_fMoveSpeed = (rand() % 20) + 30;

	VECTOR2 _vec2 = VECTOR2(0, 0);

	switch (m_eRespawnPos)
	{
	case STAR_RESPAWN_POS_LEFT:
	{
		_vec2.x = GAME_SCREEN_X - m_size.cx;
		_vec2.y = (rand() % GAME_SCREEN_HEIGHT) + GAME_SCREEN_Y;
	}
	break;
	case STAR_RESPAWN_POS_RIGHT:
	{
		_vec2.x = GAME_SCREEN_X + GAME_SCREEN_WIDTH + m_size.cx;
		_vec2.y = (rand() % GAME_SCREEN_HEIGHT) + GAME_SCREEN_Y;
	}
	break;
	case STAR_RESPAWN_POS_TOP:
	{
		_vec2.x = (rand() % GAME_SCREEN_WIDTH) + GAME_SCREEN_X;
		_vec2.y = GAME_SCREEN_Y - m_size.cy;
	}
	break;
	case STAR_RESPAWN_POS_BOTTOM:
	{
		_vec2.x = (rand() % GAME_SCREEN_WIDTH) + GAME_SCREEN_X;
		_vec2.y = GAME_SCREEN_Y + GAME_SCREEN_HEIGHT + m_size.cy;
	}
	break;
	}

	m_pStar->SetPosition(_vec2);
	m_pLabel->SetPosition(VECTOR2(_vec2.x, _vec2.y - 5));
}

void AirPlaneStar::Update(float _fElapseTime)
{
}

void AirPlaneStar::SetStarAction(bool _bFeverMode, int _iFeverScore)
{
	m_bUse = true;
	m_pStar->SetVisibility(true);
	m_pLabel->SetLabelString(std::to_string(_iFeverScore));
	m_pLabel->SetVisibility(true);

	SetStarPos(_bFeverMode);
	VECTOR2 _vec2MoveBy = m_pAirPlane->GetAirPlanePosition() - m_pStar->GetPosition();
	_vec2MoveBy.Normalize();

	m_pStar->SetMoveBy(m_fMoveSpeed, _vec2MoveBy);
	m_pLabel->SetMoveBy(m_fMoveSpeed, _vec2MoveBy);
}

void AirPlaneStar::DestroyStar()
{
	m_bUse = false;
	m_pStar->SetVisibility(false);
	m_pLabel->SetVisibility(false);
}

void AirPlaneStar::SetStarFeverScore(int _iCurFeverScore)
{
	m_pLabel->SetLabelString(std::to_string(_iCurFeverScore));
}

void AirPlaneStar::Draw(HDC hdc)
{
}

void AirPlaneStar::Release()
{
}
