#pragma once
#include "EngineDefine.h"

USING_NS_EE;

#define BULLET_MAX 20
#define AIRPLANE_CENTER VECTOR2(202, 365)
#define FEVER_TIME 5
#define GAMEOVER_TIME 3

enum AIRPLANEGAME_STATE
{
	AIRPLANEGAME_STATE_READY,
	AIRPLANEGAME_STATE_PLAY,
	AIRPLANEGAME_STATE_GAMEOVER,
	AIRPLANEGAME_STATE_END
};

class Cloud;
class AirPlane;
class Bullet;
class AirPlaneStar;
class AirPlaneGameScene : public Scene
{
private:
	HWND m_hWnd;

	EEImage* m_pBackImage;
	EEImage* m_pBackUIImage;
	EEImage* m_pReadyImage;
	EEImage* m_pFeverModeImage;
	EEImage* m_pFeverTextImage;
	EEImage* m_pTimeOverImage;
	EEButton* m_pBackBtnImage;
	EEProgressbar* m_pTimeBar;
	EEProgressbar* m_pFeverBar;
	EELabel* m_pScoreLabel;
	EELabel* m_pTimeLabel;

	AirPlane* m_pAirPlane;
	vector<Cloud*> m_vecClouds;
	vector<Bullet*> m_vecBullets;
	vector<AirPlaneStar*> m_vecStars;

	VECTOR2 m_vec2CurMouse;
	VECTOR2 m_vec2PreMouse;
	Euneick::RECT m_rcScreen;

	AIRPLANEGAME_STATE m_eGameState;
	bool m_bFeverMode;
	bool m_bPlayerMove;
	int m_iBestScore;
	int m_iScore;
	int m_iBulletRespawnCount;
	int m_iStarRespawnCount;
	int m_iCurFeverScore;
	int m_iReadyIndex;
	int m_iTimeOverIndex;
	int m_iFeverCount;
	float m_fReadyTimer;
	float m_fBulletRespawnTimer;
	float m_fBulletRespawnDuration;
	float m_fStarRespawnTimer;
	float m_fStarRespawnDuration;
	float m_fTimeBarLength;
	float m_fPlayTime;
	float m_fFeverBarMax;
	float m_fFeverTimer;
	float m_fGameOverTimer;
	float m_fTimeOverIndexTimer;

public:
	virtual void Init(HWND hWnd) {};
	virtual void Init(HWND hWnd, int _iData1, int _iData2, int _iData3);
	virtual void Update(float _fElapseTime);
	virtual bool Input(float _fElapseTime);
	virtual void Draw(HDC hdc);
	virtual void Release();

	void OperFeverModeOver();
	void UpdateBullets(float _fElapseTime);
	void OperAirPlaneDestroy();
	void UpdateStars(float _fElapseTime);
	void OperGetFeverStar();

	void OnMouseDown();
	void OnMousePress();
	void OnMouseUp();

	void SetTimeLabel(float _fElapseTime);
	void SetGameOverState();

	AirPlaneGameScene();
	virtual ~AirPlaneGameScene();
};

