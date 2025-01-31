#pragma once
#include "GlobalDefines.h"

namespace Euneick
{
	/**
	*	@brief		: Window�� �����ϴ� Ŭ����
	*	@details	: WinMain�� ȣ���Ͽ� Window�� �����ϴ� Ŭ����
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
		// WndProc�� ȣ���ϴ� �Լ�
		int StartEngine(HINSTANCE hInstance);

		EngineMain(string title, int cx, int cy);
		~EngineMain();
	};
}

