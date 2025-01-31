#pragma once
#include "EngineDefine.h"

USING_NS_EE;

enum SELECT_GAME
{
	SELECT_GAME_AIRPLANE,
	SELECT_GAME_PAPER,
	SELECT_GAME_END
};

class SelectScene : public Scene
{
private:
	HWND m_hWnd;

	EEImage* m_pBackImage;
	EEImage* m_pCurSelectGameImage;
	EEImage* m_pSelectCheck;

	EEButton* m_pStartBtn;
	EEButton* m_pBackBtn;
	EEButton* m_pGameButtons[SELECT_GAME_END];

	EELabel* m_pGameTitleLabel[SELECT_GAME_END];
	EELabel* m_pGameScoreLabel[SELECT_GAME_END];

	int m_iCurSelectGame;
	int m_iGameScore[SELECT_GAME_END];

public:
	virtual void Init(HWND hWnd);
	virtual void Init(HWND hWnd, int _iData1, int _iData2, int _iData3) {};
	virtual void Update(float _fElapseTime);
	virtual bool Input(float _fElapseTime);
	virtual void Draw(HDC hdc);
	virtual void Release();

	void ReadDataFromFile();
	void OnMouseDown();
	void OnMouseUp();

	SelectScene();
	virtual ~SelectScene();
};

