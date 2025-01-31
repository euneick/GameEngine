#include "PaperGameScene.h"
#include "ClientDefines.h"
#include "Paper.h"
#include "PaperStar.h"
#include "JsonFileIOManager.h"


PaperGameScene::PaperGameScene()
{
}


PaperGameScene::~PaperGameScene()
{
}

void PaperGameScene::Init(HWND hWnd, int _iData1, int _iData2, int _iData3)
{
	m_hWnd = hWnd;
	m_iBestScore = _iData1;

	InputManager::GetInstance()->Clear();
	InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);
	InputManager::GetInstance()->RegistKeyCode(VK_LEFT);
	InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	InputManager::GetInstance()->RegistKeyCode(VK_UP);
	InputManager::GetInstance()->RegistKeyCode(VK_DOWN);
	InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);

	m_vec2CenterPaper = VECTOR2(202, 389);

	m_eGameState = PAPERGAME_STATE_READY;
	m_bBonus = false;
	m_bFeverMode = false;
	m_iCurPaper = 0;
	m_iScore = 0;
	m_iCurFeverScore = 100;
	m_iReadyIndex = 0;
	m_iTimeOverIndex = 0;
	m_iFeverCount = 0;
	m_fReadyTimer = 0.0f;
	m_fTimeBarLength = 235.0f;
	m_fPlayTime = 45.0f;
	m_fCurFeverGauge = 0.0f;
	m_fFeverBarMax = 354.0f;
	m_fFeverTimer = FEVER_TIME;
	m_fGameOverTimer = 0.0f;
	m_fTimeOverIndexTimer = 0.0f;

	m_pBackImage = EEObjectManager::GetInstance()->CreateImage("paper_back.bmp", Z_ORDER_BACK);
	m_pBackImage->SetPosition(VECTOR2(0.0f, 109.0f));
	m_pBackImage->SetAnchorPoint(VECTOR2(0.0f, 0.0f));

	m_pBackUIImage = EEObjectManager::GetInstance()->CreateImage("UIGameScene.bmp", Z_ORDER_UI);
	m_pBackUIImage->SetPosition(VECTOR2(0.0f, 0.0f));
	m_pBackUIImage->SetAnchorPoint(VECTOR2(0.0f, 0.0f));

	m_pBackBtnImage = EEObjectManager::GetInstance()->CreateButton("UIBackButton.bmp", Z_ORDER_UI);
	m_pBackBtnImage->SetPosition(VECTOR2(379, 29));

	m_pReadyImage = EEObjectManager::GetInstance()->CreateImage("UIReadyGo0.bmp", Z_ORDER_UIOBJECT);
	m_pReadyImage->RegistBitMapFrame("UIReadyGo1.bmp");
	m_pReadyImage->SetPosition(VECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT / 2));
	m_pReadyImage->SetMoveTo(400, VECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

	m_pFeverModeImage = EEObjectManager::GetInstance()->CreateImage("UIFeverMode0.bmp", Z_ORDER_UIOBJECT);
	m_pFeverModeImage->SetPosition(VECTOR2(0.0f, 109.0f));
	m_pFeverModeImage->SetAnchorPoint(VECTOR2(0.0f, 0.0f));
	for (int i = 1; i < 4; i++)
		m_pFeverModeImage->RegistBitMapFrame("UIFeverMode" + std::to_string(i) + ".bmp");
	m_pFeverModeImage->SetVisibility(false);

	m_pTimeOverImage = EEObjectManager::GetInstance()->CreateImage("UITimeOver0.bmp", Z_ORDER_UIOBJECT);
	m_pTimeOverImage->SetPosition(VECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	for (int i = 1; i < 5; i++)
		m_pTimeOverImage->RegistBitMapFrame("UITimeOver" + std::to_string(i) + ".bmp");
	m_pTimeOverImage->SetVisibility(false);

	m_pFeverTextImage = EEObjectManager::GetInstance()->CreateImage("UIFever0.bmp", Z_ORDER_UITEXT);
	m_pFeverTextImage->SetPosition(VECTOR2(SCREEN_WIDTH / 2, 80));
	m_pFeverTextImage->RegistBitMapFrame("UIFever1.bmp");

	m_pTimeBar = EEObjectManager::GetInstance()->CreateProgressBar("UITimeBarLeft.bmp", "UITimeBarCenter.bmp", "UITimeBarRight.bmp", Z_ORDER_UIOBJECT);
	m_pTimeBar->SetPosition(VECTOR2(141, 680));
	m_pTimeBar->SetProgressBarLength(m_fTimeBarLength);

	m_pFeverBar = EEObjectManager::GetInstance()->CreateProgressBar("UIFeverBarLeft.bmp", "UIFeverBarCenter.bmp", "UIFeverBarRight.bmp", Z_ORDER_UIOBJECT);
	m_pFeverBar->SetPosition(VECTOR2(21, 66));
	m_pFeverBar->SetProgressBarLength(0);

	m_pScoreLabel = EEObjectManager::GetInstance()->CreateLabel("0", Z_ORDER_UITEXT);
	m_pScoreLabel->SetPosition(VECTOR2(SCREEN_WIDTH / 2, 30));
	m_pScoreLabel->SetLabelColor(255, 255, 255);
	m_pScoreLabel->SetLaelTextBold(true);
	m_pScoreLabel->SetLabelTextSize(17);

	m_pTimeLabel = EEObjectManager::GetInstance()->CreateLabel("45 : 00", Z_ORDER_UITEXT);
	m_pTimeLabel->SetPosition(VECTOR2(265, 685));
	m_pTimeLabel->SetLabelColor(255, 255, 255);
	m_pTimeLabel->SetLaelTextBold(true);
	m_pTimeLabel->SetLabelTextSize(15);

	for (int i = 0; i < PAPER_MAX; i++)
	{
		Paper* _pNew = new Paper();
		_pNew->Init(m_vec2CenterPaper);
		m_dqPapers.push_front(_pNew);
	}

	m_pStar = new PaperStar();
	m_pStar->Init(m_vec2CenterPaper);

	m_dqPapers[m_iCurPaper]->SetPaperZOrder(Z_ORDER_PAPER_FRONT);
}

void PaperGameScene::Update(float _fElapseTime)
{
	if (m_eGameState == PAPERGAME_STATE_READY)
	{
		m_fReadyTimer += _fElapseTime;

		if (m_fReadyTimer >= READY_TIME)
		{
			if (m_iReadyIndex == 0)
			{
				m_iReadyIndex++;
				m_pReadyImage->SetBitMapFrame(m_iReadyIndex);
			}
			else
			{
				m_eGameState = PAPERGAME_STATE_PLAY;
				m_pReadyImage->SetVisibility(false);

				m_pTimeBar->SetDecreaseByTime(m_fPlayTime);
			}

			m_fReadyTimer = 0.0;
		}
	}
	else if (m_eGameState == PAPERGAME_STATE_PLAY)
	{
		if (m_fPlayTime <= 0)
		{
			SetGameOverState();
			return;
		}

		if (m_bFeverMode)
		{
			m_fFeverTimer -= _fElapseTime;

			if (m_fFeverTimer <= 0)
				OperFeverModeOver();
		}

		for (auto iter = m_dqPapers.begin(); iter != m_dqPapers.end(); iter++)
			(*iter)->Update(_fElapseTime);

		SetTimeLabel(_fElapseTime);
	}
	else
	{
		m_fGameOverTimer += _fElapseTime;
		m_fTimeOverIndexTimer += _fElapseTime;

		if (m_fTimeOverIndexTimer >= 0.1f)
		{
			m_fTimeOverIndexTimer = 0.0f;
			m_iTimeOverIndex++;

			if (m_iTimeOverIndex > 4)
				m_iTimeOverIndex = 1;

			m_pTimeOverImage->SetBitMapFrame(m_iTimeOverIndex);
		}

		if (m_fGameOverTimer >= GAMEOVER_TIME)
		{
			SceneManager::GetInstance()->LoadScene(SCENE_INDEX_RESULT, SCENE_INDEX_PAPERGAME, m_iBestScore, m_iScore);
			return;
		}
	}
}

void PaperGameScene::SetGameOverState()
{
	m_eGameState = PAPERGAME_STATE_GAMEOVER;
	m_fPlayTime = 0.0f;
	m_pTimeLabel->SetLabelString("00 : 00");

	m_pTimeOverImage->SetVisibility(true);

	const int _iBufferLength = 1024;
	char _chReadBuffer[_iBufferLength] = { 0, };
	Json::Value _JVroot;
	Json::Reader _JRreader;
	std::string _strConfig_doc;
	Json::StyledWriter writer;
	std::string _strOutputConfig;

	if (!JsonFileIOManager::GetInstance()->ReadFromJsonFile("Resource\\ScoreData.json", _chReadBuffer, _iBufferLength))
	{
		exit(1);
		return;
	}

	_strConfig_doc = _chReadBuffer;

	if (!_JRreader.parse(_strConfig_doc, _JVroot))
	{
		exit(1);
		return;
	}

	int _iPaper = 0, _iAirPlane = 0;

	_iPaper = _JVroot["papergame"].asInt();
	_iAirPlane = _JVroot["airplanegame"].asInt();

	memset(_chReadBuffer, 0, sizeof(_chReadBuffer));
	_JVroot.clear();

	if (_iPaper < m_iScore)
		_JVroot["papergame"] = m_iScore;
	else
		_JVroot["papergame"] = _iPaper;

	_JVroot["airplanegame"] = _iAirPlane;

	_strOutputConfig = writer.write(_JVroot);

	if (!JsonFileIOManager::GetInstance()->WriteToJsonFile("Resource\\ScoreData.json", _strOutputConfig.c_str(), _strOutputConfig.length()))
	{
		exit(1);
		return;
	}
}

void PaperGameScene::SetTimeLabel(float _fElapseTime)
{
	m_fPlayTime -= _fElapseTime;

	int _iSec = (int)m_fPlayTime;
	int _iMSec = (int)((m_fPlayTime - (float)_iSec) * 100);

	if (_iSec <= 0)
		_iSec = 0;

	if (_iMSec <= 0)
		_iMSec = 0;

	string _strSec, _strMSec;

	if (_iSec < 10)
		_strSec = "0" + std::to_string(_iSec);
	else
		_strSec = std::to_string(_iSec);

	if (_iMSec < 10)
		_strMSec = "0" + std::to_string(_iMSec);
	else
		_strMSec = std::to_string(_iMSec);

	m_pTimeLabel->SetLabelString(_strSec + " : " + _strMSec);
}

bool PaperGameScene::Input(float _fElapseTime)
{
	if (m_eGameState != PAPERGAME_STATE_PLAY)
		return false;

	if (InputManager::GetInstance()->IsKeyDown(VK_LEFT))
		OperPaperAction(PAPER_DIR_LEFT);

	if (InputManager::GetInstance()->IsKeyDown(VK_RIGHT))
		OperPaperAction(PAPER_DIR_RIGHT);

	if (InputManager::GetInstance()->IsKeyDown(VK_UP))
		OperPaperAction(PAPER_DIR_UP);

	if (InputManager::GetInstance()->IsKeyDown(VK_DOWN))
		OperPaperAction(PAPER_DIR_DOWN);

	if (InputManager::GetInstance()->IsKeyDown(VK_LBUTTON))
	{
		VECTOR2 _vec2Mouse = InputManager::GetInstance()->GetMouseVec2();

		if (m_pBackBtnImage->OnButtonDown(_vec2Mouse))
			m_pBackBtnImage->SetScale(VECTOR2(1.05f, 1.05f));
	}

	if (InputManager::GetInstance()->IsKeyUp(VK_LBUTTON))
	{
		VECTOR2 _vec2Mouse = InputManager::GetInstance()->GetMouseVec2();

		m_pBackBtnImage->SetScale(VECTOR2(1.0f, 1.0f));
		if (m_pBackBtnImage->OnButtonUp(_vec2Mouse))
		{
			SceneManager::GetInstance()->LoadScene(SCENE_INDEX_SELECT);
			return false;
		}
	}

	return false;
}

void PaperGameScene::OperPaperAction(PAPER_DIR _e)
{
	if ((int)m_dqPapers[m_iCurPaper]->GetPaperState() != (int)_e)
	{
		m_iCurFeverScore = 100;
		m_pStar->OperChangeScoreLabel(m_iCurFeverScore);

		if (m_bFeverMode)
			OperFeverModeOver();

		return;
	}

	m_dqPapers[m_iCurPaper]->OperCorrectAction();
	m_iCurPaper++;

	if (m_iCurPaper >= PAPER_MAX)
		m_iCurPaper = 0;

	m_dqPapers[m_iCurPaper]->SetPaperZOrder(Z_ORDER_PAPER_FRONT);

	if (m_bBonus)
	{
		m_iScore += m_iCurFeverScore;

		m_bBonus = false;
		m_pStar->SetPaperVisibility(false);
		m_iCurFeverScore += 100;
		m_pStar->OperChangeScoreLabel(m_iCurFeverScore);
	}

	if (m_bFeverMode)
	{
		m_bBonus = true;
		m_pStar->SetPaperVisibility(true);
		m_fFeverTimer = FEVER_TIME;
	}
	else
	{
		if (m_iFeverCount + 1 >= FEVER_MODE_COUNT)
		{
			m_pFeverBar->OnIncreaseActionStop();
			float _f = m_pFeverBar->GetBarLength();
			m_pFeverBar->SetIncreaseAction(m_fFeverBarMax - _f, 100.0f);
			m_bFeverMode = true;
			m_pFeverModeImage->SetVisibility(true);
			m_pFeverModeImage->SetAnimate(0.1f);
			m_pFeverTextImage->SetBitMapFrame((int)m_bFeverMode);
		}
		else
		{
			m_pFeverBar->SetIncreaseAction(m_fFeverBarMax / FEVER_MODE_COUNT, 100.0f);
			m_iFeverCount++;
		}

		int _iRand = rand() % 3;
		if (_iRand == 0)
		{
			m_bBonus = true;
			m_pStar->SetPaperVisibility(true);
		}
	}

	m_iScore += 100;
	m_pScoreLabel->SetLabelString(std::to_string(m_iScore));
}

void PaperGameScene::OperFeverModeOver()
{
	m_bFeverMode = false;
	m_iFeverCount = 0;
	m_fFeverTimer = FEVER_TIME;

	m_pFeverModeImage->SetVisibility(false);
	m_pFeverModeImage->SetBitMapFrame(0);
	m_pFeverBar->SetProgressBarLength(0);

	m_pFeverTextImage->SetBitMapFrame((int)m_bFeverMode);
}

void PaperGameScene::Draw(HDC hdc)
{
}

void PaperGameScene::Release()
{
	for (auto iter = m_dqPapers.begin(); iter != m_dqPapers.end(); iter++)
	{
		(*iter)->Release();
		SAFE_DELETE(*iter);
	}

	SAFE_DELETE(m_pStar);

	m_dqPapers.clear();
}
