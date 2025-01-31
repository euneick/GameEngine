#pragma once
#include "GlobalDefines.h"

namespace Euneick
{
	class Scene;
	/**
	*	@brief		: Scene들을 관리하는 클래스
	*	@details	: 생성 및 등록된 Scene들을 관리하는 클래스
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class SceneManager : public SingleTon<SceneManager>
	{
	private:
		int				m_iWinCX;
		int				m_iWinCY;

		HWND			m_hWnd;

		vector<Scene*>	m_vecScenes;
		Scene*			m_curScene;
		Scene*			m_lastScene;

	public:
		// Window 너비, 높이값과 각종 매니저를 등록하는 함수
		void Init(HWND hWnd, int _iWinCX, int _iWinCY);

		// Scene을 등록하는 함수
		void RegistScene(Scene* _pScene);

		// 현재 Scene의 실시간 호출 함수
		bool Update();

		// 각종 Manager와 현재 Scene의 값들을 그리는 함수
		void Draw();

		// 저장된 Scene을 부르고 현재 Scene의 메모리는 해제하는 함수
		void LoadScene(int _iSceneIndex);
		void LoadScene(int _iSceneIndex, int _iData1, int _iData2, int _iData3);

		// 각종 Manager와 현재 Scene의 메모리를 해제하는 함수
		void Release();

		SceneManager();
		~SceneManager();
	};
}

