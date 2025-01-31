#include "IntroScene.h"
#include "ClientDefines.h"


IntroScene::IntroScene()
{
}


IntroScene::~IntroScene()
{
}

void IntroScene::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	InputManager::GetInstance()->Clear();
	InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pBackImage = EEObjectManager::GetInstance()->CreateImage("Intro_Background.bmp", 0);
	m_pBackImage->SetAnchorPoint(VECTOR2(0.0f, 0.0f));
	m_pBackImage->SetPosition(VECTOR2(0.0f, 0.0f));

	m_pTitleLabelImage = EEObjectManager::GetInstance()->CreateImage("Intro_Label.bmp", 1);
	m_pTitleLabelImage->SetPosition(VECTOR2(202, 650));
	m_pTitleLabelImage->SetToggleVisibility(0.5f);
}

void IntroScene::Update(float _fElapseTime)
{
}

bool IntroScene::Input(float _fElapseTime)
{
	if (InputManager::GetInstance()->IsKeyDown(VK_ESCAPE))
		return true;

	if (InputManager::GetInstance()->IsKeyUp(VK_LBUTTON))
		SceneManager::GetInstance()->LoadScene((int)SCENE_INDEX_RANK);

	return false;
}

void IntroScene::Draw(HDC hdc)
{
}

void IntroScene::Release()
{
}
