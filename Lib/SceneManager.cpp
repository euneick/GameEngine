#include "SceneManager.h"
#include "ResManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Scene.h"
#include "EEObjectManager.h"

namespace Euneick
{
	SceneManager::SceneManager()
	{
	}


	SceneManager::~SceneManager()
	{
	}

	void SceneManager::Init(HWND hWnd, int _iWinCX, int _iWinCY)
	{
		m_hWnd = hWnd;

		m_iWinCX = _iWinCX;
		m_iWinCY = _iWinCY;

		::RECT rcClient, rcWindow;
		GetClientRect(hWnd, &rcClient);
		GetWindowRect(hWnd, &rcWindow);

		int CXFrame = (rcWindow.right - rcWindow.left) - (rcClient.right - rcClient.left);
		int CYFrame = (rcWindow.bottom - rcWindow.top) - (rcClient.bottom - rcClient.top);

		MoveWindow(m_hWnd, 0, 0, m_iWinCX + CXFrame, m_iWinCY + CYFrame, true);

		HDC hdc = GetDC(m_hWnd);

		ResManager::GetInstance()->InitBackBuf(hdc, m_iWinCX, m_iWinCY);
		InputManager::GetInstance()->Init(m_hWnd);
		TimeManager::GetInstance()->init(false, 0);
		EEObjectManager::GetInstance()->Init();

		ReleaseDC(m_hWnd, hdc);

		m_curScene = m_vecScenes[0];

		m_curScene->Init(m_hWnd);
	}

	void SceneManager::RegistScene(Scene* _pScene)
	{
		m_vecScenes.push_back(_pScene);
	}

	bool SceneManager::Update()
	{
		InputManager::GetInstance()->Update();
		TimeManager::GetInstance()->Update();
		EEObjectManager::GetInstance()->Update(TimeManager::GetInstance()->GetElipseTime());

		m_curScene->Update(TimeManager::GetInstance()->GetElipseTime());

		if (m_curScene->Input(TimeManager::GetInstance()->GetElipseTime()))
			return true;

		Draw();

		return false;
	}

	void SceneManager::Draw()
	{
		HDC hdc = GetDC(m_hWnd);

		SetBkMode(ResManager::GetInstance()->GetBackBufDC(), TRANSPARENT);

		EEObjectManager::GetInstance()->Draw();

		//m_curScene->Draw(hdc);

		ResManager::GetInstance()->DrawBackBuf(hdc);
		ReleaseDC(m_hWnd, hdc);
	}

	void SceneManager::LoadScene(int _iSceneIndex)
	{
		EEObjectManager::GetInstance()->Release();

		m_lastScene = m_curScene;
		m_curScene = m_vecScenes[_iSceneIndex];

		m_lastScene->Release();

		m_curScene->Init(m_hWnd);
	}

	void SceneManager::LoadScene(int _iSceneIndex, int _iData1, int _iData2, int _iData3)
	{
		EEObjectManager::GetInstance()->Release();

		m_lastScene = m_curScene;
		m_curScene = m_vecScenes[_iSceneIndex];

		m_lastScene->Release();

		m_curScene->Init(m_hWnd, _iData1, _iData2, _iData3);
	}

	void SceneManager::Release()
	{
		ResManager::GetInstance()->Release();
		ResManager::GetInstance()->DestroyInstance();
		TimeManager::GetInstance()->DestroyInstance();
		InputManager::GetInstance()->Release();
		InputManager::GetInstance()->DestroyInstance();
		EEObjectManager::GetInstance()->Release();
		EEObjectManager::GetInstance()->DestroyInstance();

		m_curScene->Release();
		for (auto iter = m_vecScenes.begin(); iter != m_vecScenes.end(); iter++)
			SAFE_DELETE(*iter);
		m_vecScenes.clear();

		DestroyInstance();
	}
}
