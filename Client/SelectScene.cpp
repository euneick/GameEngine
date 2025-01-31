#include "SelectScene.h"
#include "ClientDefines.h"
#include "JsonFileIOManager.h"

SelectScene::SelectScene()
{
}


SelectScene::~SelectScene()
{
}

void SelectScene::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	InputManager::GetInstance()->Clear();
	InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);
	InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);

	ReadDataFromFile();

	m_iCurSelectGame = 0;

	m_pBackImage = EEObjectManager::GetInstance()->CreateImage("Select_BackGround.bmp", 0);
	m_pBackImage->SetPosition(VECTOR2(0.0f, 0.0f));
	m_pBackImage->SetAnchorPoint(VECTOR2(0.0f, 0.0f));

	m_pStartBtn = EEObjectManager::GetInstance()->CreateButton("Select_StartButton.bmp", 1);
	m_pStartBtn->SetPosition(VECTOR2(202, 619));

	m_pBackBtn = EEObjectManager::GetInstance()->CreateButton("Select_BackButton.bmp", 1);
	m_pBackBtn->SetPosition(VECTOR2(48, 687));

	m_pCurSelectGameImage = EEObjectManager::GetInstance()->CreateImage("Select_GameIcon0.bmp", 1);
	m_pCurSelectGameImage->RegistBitMapFrame("Select_GameIcon1.bmp");
	m_pCurSelectGameImage->SetPosition(VECTOR2(53, 213));
	m_pCurSelectGameImage->SetAnchorPoint(VECTOR2(0, 0));

	for (int i = 0; i < SELECT_GAME_END; i++)
	{
		m_pGameButtons[i] = EEObjectManager::GetInstance()->CreateButton("Select_GameIcon" + std::to_string(i) + ".bmp", 1);
		m_pGameButtons[i]->SetPosition(VECTOR2(93 + (i * 80), 327));
	}

	m_pSelectCheck = EEObjectManager::GetInstance()->CreateImage("Select_SelectCheck.bmp", 2);
	VECTOR2 _vec2 = { m_pGameButtons[m_iCurSelectGame]->GetPosition().x - (m_pGameButtons[m_iCurSelectGame]->GetObjectSize().cx / 2),
		m_pGameButtons[m_iCurSelectGame]->GetPosition().y - (m_pGameButtons[m_iCurSelectGame]->GetObjectSize().cy / 2) };
	m_pSelectCheck->SetPosition(_vec2);

	m_pGameTitleLabel[SELECT_GAME_AIRPLANE] = EEObjectManager::GetInstance()->CreateLabel("아슬아슬 비행기", 1);
	m_pGameTitleLabel[SELECT_GAME_PAPER] = EEObjectManager::GetInstance()->CreateLabel("알록달록 색종이", 1);
	m_pGameTitleLabel[SELECT_GAME_PAPER]->SetVisibility(false);
	for (int i = 0; i < SELECT_GAME_END; i++)
	{
		m_pGameTitleLabel[i]->SetPosition(VECTOR2(110, 215));
		m_pGameTitleLabel[i]->SetLabelColor(0, 0, 255);
		m_pGameTitleLabel[i]->SetLabelTextSize(15);
		m_pGameTitleLabel[i]->SetLaelTextBold(true);
		m_pGameTitleLabel[i]->SetLabelAlignment(ALIGNMENT_LEFT);
	}

	m_pGameScoreLabel[SELECT_GAME_AIRPLANE] = EEObjectManager::GetInstance()->CreateLabel(std::to_string(m_iGameScore[SELECT_GAME_AIRPLANE]), 1);
	m_pGameScoreLabel[SELECT_GAME_PAPER] = EEObjectManager::GetInstance()->CreateLabel(std::to_string(m_iGameScore[SELECT_GAME_PAPER]), 1);
	m_pGameScoreLabel[SELECT_GAME_PAPER]->SetVisibility(false);
	for (int i = 0; i < SELECT_GAME_END; i++)
	{
		m_pGameScoreLabel[i]->SetPosition(VECTOR2(110, 245));
		m_pGameScoreLabel[i]->SetLabelColor(0, 0, 255);
		m_pGameScoreLabel[i]->SetLabelTextSize(15);
		m_pGameScoreLabel[i]->SetLaelTextBold(false);
		m_pGameScoreLabel[i]->SetLabelAlignment(ALIGNMENT_LEFT);
	}
}

void SelectScene::ReadDataFromFile()
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

	m_iGameScore[SELECT_GAME_AIRPLANE] = _JVroot.get("airplanegame", 0).asInt();
	m_iGameScore[SELECT_GAME_PAPER] = _JVroot.get("papergame", 0).asInt();
}

void SelectScene::Update(float _fElapseTime)
{
}

bool SelectScene::Input(float _fElapseTime)
{
	if (InputManager::GetInstance()->IsKeyUp(VK_ESCAPE))
		SceneManager::GetInstance()->LoadScene(SCENE_INDEX_RANK);

	if (InputManager::GetInstance()->IsKeyDown(VK_LBUTTON))
		OnMouseDown();

	if (InputManager::GetInstance()->IsKeyUp(VK_LBUTTON))
		OnMouseUp();

	return false;
}

void SelectScene::OnMouseDown()
{
	VECTOR2 _vec2Mouse = InputManager::GetInstance()->GetMouseVec2();

	if (m_pStartBtn->OnButtonDown(_vec2Mouse))
		m_pStartBtn->SetScale(VECTOR2(1.05f, 1.05f));

	if (m_pBackBtn->OnButtonDown(_vec2Mouse))
		m_pBackBtn->SetScale(VECTOR2(1.05f, 1.05f));

	for (int i = 0; i < SELECT_GAME_END; i++)
	{
		if (m_pGameButtons[i]->OnButtonDown(_vec2Mouse))
		{
			m_pGameButtons[i]->SetScale(VECTOR2(1.05f, 1.05f));
		}
	}
}

void SelectScene::OnMouseUp()
{
	VECTOR2 _vec2Mouse = InputManager::GetInstance()->GetMouseVec2();

	m_pStartBtn->SetScale(VECTOR2(1.0f, 1.0f));
	m_pBackBtn->SetScale(VECTOR2(1.0f, 1.0f));

	if (m_pBackBtn->OnButtonUp(_vec2Mouse))
	{
		SceneManager::GetInstance()->LoadScene(SCENE_INDEX_RANK);
		return;
	}

	if (m_pStartBtn->OnButtonUp(_vec2Mouse))
	{
		SceneManager::GetInstance()->LoadScene((int)SCENE_INDEX_AIRPLANEGAME + m_iCurSelectGame, m_iGameScore[m_iCurSelectGame], 0, 0);
		return;
	}

	for (int i = 0; i < SELECT_GAME_END; i++)
	{
		m_pGameButtons[i]->SetScale(VECTOR2(1.0f, 1.0f));
		m_pGameTitleLabel[i]->SetVisibility(false);
		m_pGameScoreLabel[i]->SetVisibility(false);

		if (m_pGameButtons[i]->OnButtonUp(_vec2Mouse))
		{
			m_pCurSelectGameImage->SetBitMapFrame(i);
			m_iCurSelectGame = i;
		}
	}

	VECTOR2 _vec2 = { m_pGameButtons[m_iCurSelectGame]->GetPosition().x - (m_pGameButtons[m_iCurSelectGame]->GetObjectSize().cx / 2),
		m_pGameButtons[m_iCurSelectGame]->GetPosition().y - (m_pGameButtons[m_iCurSelectGame]->GetObjectSize().cy / 2) };
	m_pSelectCheck->SetPosition(_vec2);

	m_pGameTitleLabel[m_iCurSelectGame]->SetVisibility(true);
	m_pGameScoreLabel[m_iCurSelectGame]->SetVisibility(true);
}

void SelectScene::Draw(HDC hdc)
{
}

void SelectScene::Release()
{
	JsonFileIOManager::GetInstance()->DestroyInstance();
}