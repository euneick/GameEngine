#pragma once
#include "GlobalDefines.h"

namespace Euneick
{
	class Scene;
	/**
	*	@brief		: Scene���� �����ϴ� Ŭ����
	*	@details	: ���� �� ��ϵ� Scene���� �����ϴ� Ŭ����
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
		// Window �ʺ�, ���̰��� ���� �Ŵ����� ����ϴ� �Լ�
		void Init(HWND hWnd, int _iWinCX, int _iWinCY);

		// Scene�� ����ϴ� �Լ�
		void RegistScene(Scene* _pScene);

		// ���� Scene�� �ǽð� ȣ�� �Լ�
		bool Update();

		// ���� Manager�� ���� Scene�� ������ �׸��� �Լ�
		void Draw();

		// ����� Scene�� �θ��� ���� Scene�� �޸𸮴� �����ϴ� �Լ�
		void LoadScene(int _iSceneIndex);
		void LoadScene(int _iSceneIndex, int _iData1, int _iData2, int _iData3);

		// ���� Manager�� ���� Scene�� �޸𸮸� �����ϴ� �Լ�
		void Release();

		SceneManager();
		~SceneManager();
	};
}

