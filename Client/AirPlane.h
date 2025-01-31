#pragma once
#include "EngineDefine.h"

USING_NS_EE;

class AirPlane
{
private:
	EEImage* m_pAirPlaneImage;
	EEImage* m_pDestroyImage;

	bool m_bAlive;
	bool m_bDestroy;
	float m_fDestroyTimer;
	float m_fRespawnTimer;

public:
	void Init();
	void Update(float _fElapseTime);
	void Draw(HDC hdc);
	void Release();

	void OperMoveAirPlane(VECTOR2 _vec2);
	bool OnCollisionEnter(VECTOR2 _vec2Target, int _iTargetRadius);
	void SetDestroyAirPlane();
	
	void SetAirPlanePosition(VECTOR2 _vec2);
	VECTOR2 GetAirPlanePosition();
	Euneick::RECT GetAirPlaneRect();

	inline bool GetAirPlaneAlive()
	{
		return m_bAlive;
	}

	AirPlane();
	~AirPlane();
};

