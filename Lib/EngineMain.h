#pragma once
#include "GlobalDefines.h"

namespace Euneick
{
	/**
	*	@brief		: Window를 시작하는 클래스
	*	@details	: WinMain을 호출하여 Window를 시작하는 클래스
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class EngineMain
	{
	private:
		string m_strTitle;
		int m_iWinSizeX;
		int m_iWinSizeY;

	public:
		// WndProc를 호출하는 함수
		int StartEngine(HINSTANCE hInstance);

		EngineMain(string title, int cx, int cy);
		~EngineMain();
	};
}

