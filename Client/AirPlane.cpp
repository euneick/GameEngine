#include "AirPlane.h"
#include "ClientDefines.h"


AirPlane::AirPlane()
{
}


AirPlane::~AirPlane()
{
}

void AirPlane::Init()
{
	m_pAirPlaneImage = EEObjectManager::GetInstance()->CreateImage("Airplane_player0.bmp", Z_ORDER_AIRPLANE);
	m_pAirPlaneImage->RegistBitMapFrame("Airplane_player1.bmp");
	m_pAirPlaneImage->SetPosition(VECTOR2(202, 365));
	m_pAirPlaneImage->SetAnimate(0.1f);

	m_pDestroyImage = EEObjectManager::GetInstance()->CreateImage("Airplane_Exp0.bmp", Z_ORDER_AIRPLANE);
	for (int i = 1; i < 4; i++)
		m_pDestroyImage->RegistBitMapFrame("Airplane_Exp" + std::to_string(i) + ".bmp");
	m_pDestroyImage->SetPosition(VECTOR2(202, 365));
	m_pDestroyImage->SetVisibility(false);

	m_bAlive = true;
	m_bDestroy = false;
	m_fDestroyTimer = 0.0f;
	m_fRespawnTimer = 0.0f;

	m_pAirPlaneImage->SetColliderRadius(m_pAirPlaneImage->GetObjectSize().cx / 3);
}

void AirPlane::Update(float _fElapseTime)
{
	if (m_bDestroy)
	{
		m_fDestroyTimer += _fElapseTime;

		if (m_fDestroyTimer >= 0.6f)
		{
			m_bDestroy = false;
			m_fDestroyTimer = 0.0f;
			m_pDestroyImage->SetVisibility(false);
			m_pDestroyImage->SetBitMapFrame(0);
		}
	}

	if (!m_bAlive)
	{
		m_fRespawnTimer += _fElapseTime;

		if (m_fRespawnTimer >= 1.0f)
		{
			m_bAlive = true;
			m_fRespawnTimer = 0.0f;

			m_pAirPlaneImage->SetVisibility(true);
		}
	}
}

void AirPlane::Draw(HDC hdc)
{
}

void AirPlane::Release()
{
}

void AirPlane::OperMoveAirPlane(VECTOR2 _vec2)
{
	m_pAirPlaneImage->SetPosition(m_pAirPlaneImage->GetPosition() + _vec2);
}

bool AirPlane::OnCollisionEnter(VECTOR2 _vec2Target, int _iTargetRadius)
{
	if (m_bDestroy)
		return false;

	if (m_pAirPlaneImage->IntersectCircle(_vec2Target, _iTargetRadius))
		return true;

	return false;
}

void AirPlane::SetDestroyAirPlane()
{
	m_bDestroy = true;
	m_bAlive = false;
	m_pAirPlaneImage->SetVisibility(false);
	m_pDestroyImage->SetVisibility(true);
	m_pDestroyImage->SetPosition(m_pAirPlaneImage->GetPosition());
	m_pDestroyImage->SetAnimate(0.6f, 0.15f);
}

void AirPlane::SetAirPlanePosition(VECTOR2 _vec2)
{
	m_pAirPlaneImage->SetPosition(_vec2);
}

VECTOR2 AirPlane::GetAirPlanePosition()
{
	return m_pAirPlaneImage->GetPosition();
}

Euneick::RECT AirPlane::GetAirPlaneRect()
{
	return m_pAirPlaneImage->GetObjectRect();
}