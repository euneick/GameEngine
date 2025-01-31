#include "EngineMain.h"
#include "SceneManager.h"
#include <crtdbg.h>

namespace Euneick
{
	EngineMain::EngineMain(string title, int cx, int cy)
	{
		m_strTitle = title;
		m_iWinSizeX = cx;
		m_iWinSizeY = cy;
	}


	EngineMain::~EngineMain()
	{
	}

	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	int EngineMain::StartEngine(HINSTANCE hInstance)
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		_CrtDumpMemoryLeaks();
		//_CrtSetBreakAlloc(286);

		MSG Message;
		WNDCLASS WndClass;

		WndClass.cbClsExtra = 0;
		WndClass.cbWndExtra = 0;
		WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		WndClass.hInstance = hInstance;
		WndClass.lpfnWndProc = WndProc;
		WndClass.lpszClassName = m_strTitle.c_str();
		WndClass.lpszMenuName = NULL;
		WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		RegisterClass(&WndClass);

		HWND hWnd = CreateWindow(m_strTitle.c_str(), m_strTitle.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
		ShowWindow(hWnd, SW_SHOWDEFAULT);

		SceneManager::GetInstance()->Init(hWnd, m_iWinSizeX, m_iWinSizeY);

		while (true)
		{
			/// 메시지큐에 메시지가 있으면 메시지 처리
			if (PeekMessage(&Message, NULL, 0U, 0U, PM_REMOVE))
			{
				if (Message.message == WM_QUIT)
					break;

				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}
			else
			{
				if (SceneManager::GetInstance()->Update())
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
				}
			}
		}

		SceneManager::GetInstance()->Release();

		return (int)Message.wParam;
	}

	LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
	{
		switch (iMessage)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

		return(DefWindowProc(hWnd, iMessage, wParam, lParam));
	}
}