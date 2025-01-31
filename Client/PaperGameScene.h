#pragma once
#include "EngineDefine.h"
#include <deque>

using namespace std;
USING_NS_EE;

#define PAPER_MAX 5
#define FEVER_TIME 5
#define GAMEOVER_TIME 3

enum PAPERGAME_STATE
{
	PAPERGAME_STATE_READY,
	PAPERGAME_STATE_PLAY,
	PAPERGAME_STATE_GAMEOVER,
	PAPERGAME_STATE_END
};

enum PAPER_DIR
{
	PAPER_DIR_LEFT,
	PAPER_DIR_RIGHT,
	PAPER_DIR_UP,
	PAPER_DIR_DOWN,
	PAPER_DIR_END
};

class PaperStar;
class Paper;
class PaperGameScene : public Scene
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

	deque<Paper*> m_dqPapers;
	PaperStar* m_pStar;

	VECTOR2 m_vec2CenterPaper;

	PAPERGAME_STATE m_eGameState;
	bool m_bFeverMode;
	bool m_bBonus;
	int m_iBestScore;
	int m_iCurPaper;
	int m_iScore;
	int m_iCurFeverScore;
	int m_iReadyIndex;
	int m_iTimeOverIndex;
	int m_iFeverCount;
	float m_fReadyTimer;
	float m_fTimeBarLength;
	float m_fPlayTime;
	float m_fCurFeverGauge;
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

	void OperPaperAction(PAPER_DIR _e);
	void SetTimeLabel(float _fElapseTime);
	void SetGameOverState();
	void OperFeverModeOver();

	PaperGameScene();
	virtual ~PaperGameScene();
};

