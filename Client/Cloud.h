#pragma once
#include "EngineDefine.h"

USING_NS_EE;

#define CLOUD_FRAME_MAX 4

class Cloud
{
private:
	EEImage* m_pCloud;

	float m_fCloudSizeCY;
	float m_fRespawnY;
	float m_fMoveToY;

public:
	void Init();
	void Update(float _fElapseTime);
	void Draw(HDC hdc);
	void Release();

	void OperMove();

	Cloud();
	~Cloud();
};

