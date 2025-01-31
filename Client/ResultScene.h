#pragma once
#include "EngineDefine.h"

USING_NS_EE;

class ResultScene : public Scene
{
private:
	HWND m_hWnd;

	EEImage* m_pBackImage;
	EEButton* m_pRetryBtn;
	EEButton* m_pContinueBtn;
	EELabel* m_pBestScoreLabel;
	EELabel* m_pScoreLabel;

	bool m_bBestScoreMode;
	int m_iCurSceneIndex;
	int m_iBestScore;
	int m_iGameScore;
	int m_iRetryBtnY;

public:
	virtual void Init(HWND hWnd) {};
	virtual void Init(HWND hWnd, int _iData1, int _iData2, int _iData3);
	virtual void Update(float _fElapseTime);
	virtual bool Input(float _fElapseTime);
	virtual void Draw(HDC hdc);
	virtual void Release();

	ResultScene();
	virtual ~ResultScene();
};

