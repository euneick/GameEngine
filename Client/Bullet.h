#pragma once
#include "EngineDefine.h"

USING_NS_EE;

enum BULLET_RESPAWN_POS
{
	BULLET_RESPAWN_POS_LEFT,
	BULLET_RESPAWN_POS_RIGHT,
	BULLET_RESPAWN_POS_TOP,
	BULLET_RESPAWN_POS_BOTTOM,
	BULLET_RESPAWN_POS_END
};

class AirPlane;
class Bullet
{
private:
	AirPlane* m_pAirPlane;

	EEImage* m_pBullet;

	SIZE m_size;

	BULLET_RESPAWN_POS m_eRespawnPos;
	bool m_bUse;
	float m_fMoveSpeed;

public:
	void Init(AirPlane* _pAirPlane);
	void SetBulletPos();
	void Update(float _fElapseTime);
	void SetBulletAction();
	void DestroyBullet();
	void Draw(HDC hdc);
	void Release();

	inline bool IsUse()
	{
		return m_bUse;
	}

	inline VECTOR2 GetBulletPos()
	{
		return m_pBullet->GetPosition();
	}

	inline int GetBulletColliderRadius()
	{
		return m_pBullet->GetColliderRadius();
	}

	Bullet();
	~Bullet();
};

