#include "Bullet.h"
#include "ClientDefines.h"
#include "AirPlane.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet::Init(AirPlane* _pAirPlane)
{
	m_pAirPlane = _pAirPlane;

	m_pBullet = EEObjectManager::GetInstance()->CreateImage("Airplane_bullet.bmp", Z_ORDER_BULLET);
	m_pBullet->SetVisibility(false);

	m_size = m_pBullet->GetObjectSize();

	m_pBullet->SetColliderRadius(m_size.cx / 2);

	m_eRespawnPos = BULLET_RESPAWN_POS_END;
	m_bUse = false;
	m_fMoveSpeed = false;
}

void Bullet::SetBulletPos()
{
	int _iRespawnPos = rand() % 4;
	m_eRespawnPos = (BULLET_RESPAWN_POS)_iRespawnPos;
	m_fMoveSpeed = (rand() % 100) + 50;

	VECTOR2 _vec2 = VECTOR2(0, 0);

	switch (m_eRespawnPos)
	{
	case BULLET_RESPAWN_POS_LEFT:
	{
		_vec2.x = GAME_SCREEN_X - m_size.cx;
		_vec2.y = (rand() % GAME_SCREEN_HEIGHT) + GAME_SCREEN_Y;
	}
	break;
	case BULLET_RESPAWN_POS_RIGHT:
	{
		_vec2.x = GAME_SCREEN_X + GAME_SCREEN_WIDTH + m_size.cx;
		_vec2.y = (rand() % GAME_SCREEN_HEIGHT) + GAME_SCREEN_Y;
	}
	break;
	case BULLET_RESPAWN_POS_TOP:
	{
		_vec2.x = (rand() % GAME_SCREEN_WIDTH) + GAME_SCREEN_X;
		_vec2.y = GAME_SCREEN_Y - m_size.cy;
	}
	break;
	case BULLET_RESPAWN_POS_BOTTOM:
	{
		_vec2.x = (rand() % GAME_SCREEN_WIDTH) + GAME_SCREEN_X;
		_vec2.y = GAME_SCREEN_Y + GAME_SCREEN_HEIGHT + m_size.cy;
	}
	break;
	}

	m_pBullet->SetPosition(_vec2);
}

void Bullet::Update(float _fElapseTime)
{
}

void Bullet::SetBulletAction()
{
	m_bUse = true;
	m_pBullet->SetVisibility(true);

	SetBulletPos();
	VECTOR2 _vec2MoveBy = m_pAirPlane->GetAirPlanePosition() - m_pBullet->GetPosition();
	_vec2MoveBy.Normalize();

	m_pBullet->SetMoveBy(m_fMoveSpeed, _vec2MoveBy);
}

void Bullet::DestroyBullet()
{
	m_bUse = false;
	m_pBullet->SetVisibility(false);
}

void Bullet::Draw(HDC hdc)
{
}

void Bullet::Release()
{
}