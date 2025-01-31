#pragma once
#include "EngineDefine.h"

USING_NS_EE;

class RankScene : public Scene
{
private:
	HWND m_hWnd;

	EEImage* m_pBackImage;
	EEButton* m_pStartBtn;
	EELabel* m_pPlayerLabel;
	EELabel* m_pTotalScoreLabel;

	string m_strTotalScore;

public:
	virtual void Init(HWND hWnd);
	virtual void Init(HWND hWnd, int _iData1, int _iData2, int _iData3) {};
	virtual void Update(float _fElapseTime);
	virtual bool Input(float _fElapseTime);
	virtual void Draw(HDC hdc);
	virtual void Release();

	void SetTotalScoreString();

	RankScene();
	virtual ~RankScene();
};

