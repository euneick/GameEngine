#include "ResultScene.h"
#include "ClientDefines.h"



ResultScene::ResultScene()
{
}


ResultScene::~ResultScene()
{
}

void ResultScene::Init(HWND hWnd, int _iData1, int _iData2, int _iData3)
{
	m_hWnd = hWnd;
	m_iCurSceneIndex = _iData1;
	m_iBestScore = _iData2;
	m_iGameScore = _iData3;
	
	InputManager::GetInstance()->Clear();
	InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	if (m_iBestScore < m_iGameScore)
		m_bBestScoreMode = true;
	else
		m_bBestScoreMode = false;

	if (m_bBestScoreMode)
	{
		m_pBackImage = EEObjectManager::GetInstance()->CreateImage("Result_Best0.bmp", Z_ORDER_BACK);
		for (int i = 1; i < 3; i++)
			m_pBackImage->RegistBitMapFrame("Result_Best" + std::to_string(i) + ".bmp");
		m_pBackImage->SetAnimate(0.1f);

		m_iRetryBtnY = 574;

		m_pBestScoreLabel = EEObjectManager::GetInstance()->CreateLabel(std::to_string(m_iGameScore), Z_ORDER_UITEXT);
		m_pBestScoreLabel->SetPosition(VECTOR2(SCREEN_WIDTH / 2, 260));
		m_pBestScoreLabel->SetLabelColor(0, 0, 255);
		m_pBestScoreLabel->SetLabelTextSize(40);
		m_pBestScoreLabel->SetLaelTextBold(true);
	}
	else
	{
		m_pBackImage = EEObjectManager::GetInstance()->CreateImage("Result_Normal.bmp", Z_ORDER_BACK);

		m_iRetryBtnY = 584;

		m_pBestScoreLabel = EEObjectManager::GetInstance()->CreateLabel(std::to_string(m_iBestScore), Z_ORDER_UITEXT);
		m_pBestScoreLabel->SetPosition(VECTOR2(295, 120));
		m_pBestScoreLabel->SetLabelColor(0, 0, 0);
		m_pBestScoreLabel->SetLabelTextSize(15);
		m_pBestScoreLabel->SetLabelAlignment(ALIGNMENT_LEFT);
		m_pBestScoreLabel->SetLaelTextBold(true);

		m_pScoreLabel = EEObjectManager::GetInstance()->CreateLabel(std::to_string(m_iGameScore), Z_ORDER_UITEXT);
		m_pScoreLabel->SetPosition(VECTOR2(SCREEN_WIDTH / 2, 260));
		m_pScoreLabel->SetLabelColor(0, 0, 255);
		m_pScoreLabel->SetLabelTextSize(40);
		m_pScoreLabel->SetLaelTextBold(true);
	}

	m_pBackImage->SetAnchorPoint(VECTOR2(0.0f, 0.0f));
	m_pBackImage->SetPosition(VECTOR2(0.0f, 0.0f));

	m_pRetryBtn = EEObjectManager::GetInstance()->CreateButton("Result_Retry.bmp", Z_ORDER_UIBTN);
	m_pRetryBtn->SetPosition(VECTOR2(SCREEN_WIDTH / 2, m_iRetryBtnY));

	m_pContinueBtn = EEObjectManager::GetInstance()->CreateButton("Result_Continue.bmp", Z_ORDER_UIBTN);
	m_pContinueBtn->SetPosition(VECTOR2(SCREEN_WIDTH / 2, 667));
}

void ResultScene::Update(float _fElapseTime)
{
}

bool ResultScene::Input(float _fElapseTime)
{
	if (InputManager::GetInstance()->IsKeyDown(VK_LBUTTON))
	{
		VECTOR2 _vec2Mouse = InputManager::GetInstance()->GetMouseVec2();

		if (m_pRetryBtn->OnButtonDown(_vec2Mouse))
			m_pRetryBtn->SetScale(VECTOR2(1.05f, 1.05f));

		if (m_pContinueBtn->OnButtonDown(_vec2Mouse))
			m_pContinueBtn->SetScale(VECTOR2(1.05f, 1.05f));
	}

	if (InputManager::GetInstance()->IsKeyUp(VK_LBUTTON))
	{
		VECTOR2 _vec2Mouse = InputManager::GetInstance()->GetMouseVec2();

		m_pRetryBtn->SetScale(VECTOR2(1.0f, 1.0f));
		if (m_pRetryBtn->OnButtonUp(_vec2Mouse))
		{
			if (m_bBestScoreMode)
				SceneManager::GetInstance()->LoadScene(m_iCurSceneIndex, m_iGameScore, 0, 0);
			else
				SceneManager::GetInstance()->LoadScene(m_iCurSceneIndex, m_iBestScore, 0, 0);

			return false;
		}

		m_pContinueBtn->SetScale(VECTOR2(1.0f, 1.0f));
		if (m_pContinueBtn->OnButtonUp(_vec2Mouse))
		{
			SceneManager::GetInstance()->LoadScene(SCENE_INDEX_SELECT);
			return false;
		}
	}

	return false;
}

void ResultScene::Draw(HDC hdc)
{
}

void ResultScene::Release()
{
}
