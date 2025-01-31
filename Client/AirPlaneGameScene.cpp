#include "AirPlaneGameScene.h"
#include "ClientDefines.h"
#include "JsonFileIOManager.h"
#include "AirPlane.h"
#include "Cloud.h"
#include "Bullet.h"
#include "AirPlaneStar.h"


AirPlaneGameScene::AirPlaneGameScene()
{
}


AirPlaneGameScene::~AirPlaneGameScene()
{
}

void AirPlaneGameScene::Init(HWND hWnd, int _iData1, int _iData2, int _iData3)
{
	m_hWnd = hWnd;
	m_iBestScore = _iData1;

	InputManager::GetInstance()->Clear();
	InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);
	InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);

	m_eGameState = AIRPLANEGAME_STATE_READY;
	m_bFeverMode = false;
	m_bPlayerMove = false;
	m_iReadyIndex = 0;
	m_iScore = 0;
	m_iBulletRespawnCount = 0;
	m_iStarRespawnCount = 0;
	m_iCurFeverScore = 100;
	m_iTimeOverIndex = 0;
	m_iFeverCount = 0;
	m_fReadyTimer = 0.0f;
	m_fBulletRespawnTimer = 0.0f;
	m_fBulletRespawnDuration = 0.5f;
	m_fStarRespawnTimer = 0.0f;
	m_fStarRespawnDuration = 1.0f;
	m_fTimeBarLength = 235.0f;
	m_fPlayTime = 45.0f;
	m_fFeverBarMax = 354.0f;
	m_fFeverTimer = FEVER_TIME;
	m_fGameOverTimer = 0.0f;
	m_fTimeOverIndexTimer = 0.0f;

	m_pBackImage = EEObjectManager::GetInstance()->CreateImage("Airplane_back.bmp", Z_ORDER_BACK);
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

	m_pAirPlane = new AirPlane();
	m_pAirPlane->Init();

	for (int i = 0; i < 10; i++)
	{
		Cloud* _pNew = new Cloud();
		_pNew->Init();
		m_vecClouds.push_back(_pNew);
	}

	for (int i = 0; i < BULLET_MAX; i++)
	{
		Bullet* _pNew = new Bullet();
		_pNew->Init(m_pAirPlane);
		m_vecBullets.push_back(_pNew);
	}

	for (int i = 0; i < 50; i++)
	{
		AirPlaneStar* _pNew = new AirPlaneStar();
		_pNew->Init(m_pAirPlane);
		m_vecStars.push_back(_pNew);
	}

	m_rcScreen = { (float)GAME_SCREEN_X - 75,(float)GAME_SCREEN_Y - 75,
		(float)GAME_SCREEN_X + (float)GAME_SCREEN_WIDTH + 75,(float)GAME_SCREEN_Y + (float)GAME_SCREEN_HEIGHT + 75 };
}

void AirPlaneGameScene::Update(float _fElapseTime)
{
	if (m_eGameState == AIRPLANEGAME_STATE_READY)
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
				m_eGameState = AIRPLANEGAME_STATE_PLAY;
				m_pReadyImage->SetVisibility(false);

				for (auto iter = m_vecClouds.begin(); iter != m_vecClouds.end(); iter++)
					(*iter)->OperMove();

				m_pTimeBar->SetDecreaseByTime(m_fPlayTime);
			}

			m_fReadyTimer = 0.0;
		}
	}
	else if (m_eGameState == AIRPLANEGAME_STATE_PLAY)
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

		m_pAirPlane->Update(_fElapseTime);

		for (auto iter = m_vecClouds.begin(); iter != m_vecClouds.end(); iter++)
			(*iter)->Update(_fElapseTime);

		if (m_pAirPlane->GetAirPlaneAlive())
		{
			UpdateBullets(_fElapseTime);
			UpdateStars(_fElapseTime);
		}

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
			SceneManager::GetInstance()->LoadScene(SCENE_INDEX_RESULT, SCENE_INDEX_AIRPLANEGAME, m_iBestScore, m_iScore);
			return;
		}
	}
}

void AirPlaneGameScene::OperFeverModeOver()
{
	m_bFeverMode = false;
	m_iFeverCount = 0;
	m_fFeverTimer = FEVER_TIME;
	m_fStarRespawnDuration = 1.0f;

	m_pFeverModeImage->SetVisibility(false);
	m_pFeverModeImage->SetBitMapFrame(0);
	m_pFeverBar->SetProgressBarLength(0);

	m_pFeverTextImage->SetBitMapFrame((int)m_bFeverMode);
}

void AirPlaneGameScene::UpdateBullets(float _fElapseTime)
{
	m_fBulletRespawnTimer += _fElapseTime;

	if (m_fBulletRespawnTimer >= m_fBulletRespawnDuration && m_iBulletRespawnCount < BULLET_MAX)
	{
		m_fBulletRespawnTimer = 0.0f;
		for (auto iter = m_vecBullets.begin(); iter != m_vecBullets.end(); iter++)
		{
			if (!(*iter)->IsUse())
			{
				m_iBulletRespawnCount++;
				(*iter)->SetBulletAction();
				break;
			}
		}
	}

	for (auto iter = m_vecBullets.begin(); iter != m_vecBullets.end(); iter++)
	{
		if (!(*iter)->IsUse())
			continue;

		if (m_pAirPlane->OnCollisionEnter((*iter)->GetBulletPos(), (*iter)->GetBulletColliderRadius()))
		{
			OperAirPlaneDestroy();
			break;
		}

		if (!m_rcScreen.IsVec2InRect((*iter)->GetBulletPos()))
		{
			m_iBulletRespawnCount--;
			(*iter)->DestroyBullet();
		}
	}
}

void AirPlaneGameScene::OperAirPlaneDestroy()
{
	m_pAirPlane->SetDestroyAirPlane();
	m_pAirPlane->SetAirPlanePosition(AIRPLANE_CENTER);
	m_iBulletRespawnCount = 0;
	m_iStarRespawnCount = 0;
	m_iCurFeverScore = 100;

	for (auto iter = m_vecBullets.begin(); iter != m_vecBullets.end(); iter++)
	{
		(*iter)->DestroyBullet();
	}

	for (auto iter = m_vecStars.begin(); iter != m_vecStars.end(); iter++)
	{
		(*iter)->SetStarFeverScore(m_iCurFeverScore);
		(*iter)->DestroyStar();
	}

	if (m_bFeverMode)
		OperFeverModeOver();
}

void AirPlaneGameScene::UpdateStars(float _fElapseTime)
{
	m_fStarRespawnTimer += _fElapseTime;

	if (m_fStarRespawnTimer >= m_fStarRespawnDuration)
	{
		m_fStarRespawnTimer = 0.0f;

		for (auto iter = m_vecStars.begin(); iter != m_vecStars.end(); iter++)
		{
			if (!(*iter)->IsUse())
			{
				m_iStarRespawnCount++;
				(*iter)->SetStarAction(m_bFeverMode, m_iCurFeverScore);
				return;
			}
		}
	}

	for (auto iter = m_vecStars.begin(); iter != m_vecStars.end(); iter++)
	{
		if (!(*iter)->IsUse())
			continue;

		if (m_pAirPlane->OnCollisionEnter((*iter)->GetStarPos(), (*iter)->GetStarColliderRadius()))
		{
			m_iStarRespawnCount--;
			(*iter)->DestroyStar();
			OperGetFeverStar();
		}

		if (!m_rcScreen.IsVec2InRect((*iter)->GetStarPos()))
		{
			m_iStarRespawnCount--;
			(*iter)->DestroyStar();
		}

		(*iter)->Update(_fElapseTime);
	}
}

void AirPlaneGameScene::OperGetFeverStar()
{
	m_iScore += m_iCurFeverScore;
	m_iCurFeverScore += 100;

	for (auto iter = m_vecStars.begin(); iter != m_vecStars.end(); iter++)
	{
		(*iter)->SetStarFeverScore(m_iCurFeverScore);
	}

	m_pScoreLabel->SetLabelString(std::to_string(m_iScore));

	if (m_bFeverMode)
	{
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

			m_fStarRespawnDuration = 0.2f;
		}
		else
		{
			m_pFeverBar->SetIncreaseAction(m_fFeverBarMax / FEVER_MODE_COUNT, 100.0f);
			m_iFeverCount++;
		}
	}
}

bool AirPlaneGameScene::Input(float _fElapseTime)
{
	if (m_eGameState != AIRPLANEGAME_STATE_PLAY)
		return false;

	if (InputManager::GetInstance()->IsKeyDown(VK_LBUTTON))
		OnMouseDown();

	if (InputManager::GetInstance()->IsKeyPress(VK_LBUTTON))
		OnMousePress();

	if (InputManager::GetInstance()->IsKeyUp(VK_LBUTTON))
		OnMouseUp();

	return false;
}

void AirPlaneGameScene::OnMouseDown()
{
	VECTOR2 _vec2Mouse = InputManager::GetInstance()->GetMouseVec2();

	if (m_pBackImage->GetObjectRect().IsVec2InRect(_vec2Mouse) && m_pAirPlane->GetAirPlaneAlive())
	{
		m_bPlayerMove = true;
		m_vec2CurMouse = _vec2Mouse;
		m_vec2PreMouse = _vec2Mouse;
	}

	if (m_pBackBtnImage->OnButtonDown(_vec2Mouse))
		m_pBackBtnImage->SetScale(VECTOR2(1.05f, 1.05f));
}

void AirPlaneGameScene::OnMousePress()
{
	if (m_bPlayerMove)
	{
		m_vec2CurMouse = InputManager::GetInstance()->GetMouseVec2();

		VECTOR2 _vec2 = m_vec2CurMouse - m_vec2PreMouse;

		m_pAirPlane->OperMoveAirPlane(_vec2);

		m_vec2PreMouse = m_vec2CurMouse;
	}
}

void AirPlaneGameScene::OnMouseUp()
{
	VECTOR2 _vec2Mouse = InputManager::GetInstance()->GetMouseVec2();

	m_bPlayerMove = false;

	m_pBackBtnImage->SetScale(VECTOR2(1.0f, 1.0f));
	if(m_pBackBtnImage->OnButtonUp(_vec2Mouse))
	{
		SceneManager::GetInstance()->LoadScene(SCENE_INDEX_SELECT);
		return;
	}
}

void AirPlaneGameScene::SetTimeLabel(float _fElapseTime)
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

void AirPlaneGameScene::SetGameOverState()
{
	m_eGameState = AIRPLANEGAME_STATE_GAMEOVER;
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

	if (_iAirPlane < m_iScore)
		_JVroot["airplanegame"] = m_iScore;
	else
		_JVroot["airplanegame"] = _iAirPlane;

	_JVroot["papergame"] = _iPaper;

	_strOutputConfig = writer.write(_JVroot);

	if (!JsonFileIOManager::GetInstance()->WriteToJsonFile("Resource\\ScoreData.json", _strOutputConfig.c_str(), _strOutputConfig.length()))
	{
		exit(1);
		return;
	}
}

void AirPlaneGameScene::Draw(HDC hdc)
{
}

void AirPlaneGameScene::Release()
{
	for (auto iter = m_vecClouds.begin(); iter != m_vecClouds.end(); iter++)
		SAFE_DELETE(*iter);
	m_vecClouds.clear();

	for (auto iter = m_vecBullets.begin(); iter != m_vecBullets.end(); iter++)
		SAFE_DELETE(*iter);
	m_vecBullets.clear();

	for (auto iter = m_vecStars.begin(); iter != m_vecStars.end(); iter++)
		SAFE_DELETE(*iter);
	m_vecStars.clear();

	SAFE_DELETE(m_pAirPlane);
}