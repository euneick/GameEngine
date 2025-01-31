#include "RankScene.h"
#include "ClientDefines.h"
#include "JsonFileIOManager.h"

RankScene::RankScene()
{
}


RankScene::~RankScene()
{
}

void RankScene::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	InputManager::GetInstance()->Clear();
	InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);
	InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);

	m_pBackImage = EEObjectManager::GetInstance()->CreateImage("Rank_BackGround.bmp", Z_ORDER_BACK);
	m_pBackImage->SetPosition(VECTOR2(0.0f, 0.0f));
	m_pBackImage->SetAnchorPoint(VECTOR2(0.0f, 0.0f));

	m_pStartBtn = EEObjectManager::GetInstance()->CreateButton("Rank_StartButton.bmp", Z_ORDER_UIBTN);
	m_pStartBtn->SetPosition(VECTOR2(202, 619));

	m_pPlayerLabel = EEObjectManager::GetInstance()->CreateLabel("Player1", Z_ORDER_UILABEL);
	m_pPlayerLabel->SetPosition(VECTOR2(150, 250));
	m_pPlayerLabel->SetLabelColor(0, 0, 255);
	m_pPlayerLabel->SetLabelTextSize(20);
	m_pPlayerLabel->SetLaelTextBold(true);
	m_pPlayerLabel->SetLabelAlignment(ALIGNMENT_LEFT);

	SetTotalScoreString();

	m_pTotalScoreLabel = EEObjectManager::GetInstance()->CreateLabel(m_strTotalScore, Z_ORDER_UILABEL);
	m_pTotalScoreLabel->SetPosition(VECTOR2(150, 280));
	m_pTotalScoreLabel->SetLabelColor(0, 0, 255);
	m_pTotalScoreLabel->SetLabelTextSize(15);
	m_pTotalScoreLabel->SetLaelTextBold(false);
	m_pTotalScoreLabel->SetLabelAlignment(ALIGNMENT_LEFT);
}

void RankScene::SetTotalScoreString()
{
	const int _iBufferLength = 1024;
	char _chReadBuffer[_iBufferLength] = { 0, };
	Json::Value _JVroot;
	Json::Reader _JRreader;
	std::string _strConfig_doc;

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

	int _iAirPlaneScore = _JVroot.get("airplanegame", 0).asInt();
	int _iPaperScore = _JVroot.get("papergame", 0).asInt();

	if (_iAirPlaneScore == 0 && _iPaperScore == 0)
		m_strTotalScore = "점수없음";
	else
	{
		int _iTotalScore = _iAirPlaneScore + _iPaperScore;
		m_strTotalScore = std::to_string(_iTotalScore);
	}
}

void RankScene::Update(float _fElapseTime)
{
}

bool RankScene::Input(float _fElapseTime)
{
	if (InputManager::GetInstance()->IsKeyDown(VK_LBUTTON))
		if (m_pStartBtn->OnButtonDown(InputManager::GetInstance()->GetMouseVec2()))
			m_pStartBtn->SetScale(VECTOR2(1.05f, 1.05f));

	if (InputManager::GetInstance()->IsKeyUp(VK_LBUTTON))
	{
		m_pStartBtn->SetScale(VECTOR2(1.0f, 1.0f));
		if (m_pStartBtn->OnButtonUp(InputManager::GetInstance()->GetMouseVec2()))
		{
			SceneManager::GetInstance()->LoadScene((int)SCENE_INDEX_SELECT);
		}
	}

	if (InputManager::GetInstance()->IsKeyUp(VK_ESCAPE))
		return true;

	return false;
}

void RankScene::Draw(HDC hdc)
{
}

void RankScene::Release()
{
	JsonFileIOManager::GetInstance()->DestroyInstance();
}