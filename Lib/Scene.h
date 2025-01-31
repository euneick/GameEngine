#pragma once
#include <Windows.h>

namespace Euneick
{
	/**
	*	@brief		: Scene���� �θ� Ŭ����
	*	@details	: Scene�� �����ؾ� �ϴ� �׸��� ���� �����Լ��� ������ �ִ� Ŭ����
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class Scene
	{
	public:
		virtual void Init(HWND hWnd) = 0;
		virtual void Init(HWND hWnd, int _iData1, int _iData2, int _iData3) = 0;
		virtual void Update(float _fElapseTime) = 0;
		virtual bool Input(float _fElapseTime) = 0;
		virtual void Draw(HDC hdc) = 0;
		virtual void Release() = 0;

		Scene();
		virtual ~Scene();
	};


}