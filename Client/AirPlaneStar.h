#pragma once
#include "EngineDefine.h"

USING_NS_EE;

enum STAR_RESPAWN_POS
{
	STAR_RESPAWN_POS_LEFT,
	STAR_RESPAWN_POS_RIGHT,
	STAR_RESPAWN_POS_TOP,
	STAR_RESPAWN_POS_BOTTOM,
	STAR_RESPAWN_POS_END
};

class AirPlane;
class AirPlaneStar
{
private:
	AirPlane* m_pAirPlane;

	EEImage* m_pStar;
	EELabel* m_pLabel;

	SIZE m_size;

	STAR_RESPAWN_POS m_eRespawnPos;
	bool m_bUse;
	float m_fMoveSpeed;

public:
	void Init(AirPlane* _pAirPlane);
	void SetStarPos(bool _bFeverMode);
	void Update(float _fElapseTime);
	void SetStarAction(bool _bFeverMode, int _iFeverScore);
	void DestroyStar();
	void SetStarFeverScore(int _iCurFeverScore);
	void Draw(HDC hdc);
	void Release();

	inline bool IsUse()
	{
		return m_bUse;
	}

	inline VECTOR2 GetStarPos()
	{
		return m_pStar->GetPosition();
	}

	inline int GetStarColliderRadius()
	{
		return m_pStar->GetColliderRadius();
	}

	AirPlaneStar();
	~AirPlaneStar();
};

