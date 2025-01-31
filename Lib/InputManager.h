#pragma once
#include "GlobalDefines.h"
#include "VECTOR2.h"

namespace Euneick
{
	/**
	*	@brief		: Input �����͸� �����ϴ� Ŭ����
	*	@details	: ���콺, Ű������ �����͸� ����ϰ�, �̸� �����ϴ� Ŭ����
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class InputManager : public SingleTon<InputManager>
	{
		struct KEY_INFO
		{
		public:
			int		KeyCode;
			bool	KeyPress;
			bool	KeyUp;
			bool	KeyDown;
		};
	private:
		HWND				m_hWnd;
		VECTOR2				m_vec2Mouse;
		vector<KEY_INFO>	m_vecKeyInfo;

	public:
		// �ش� KeyCode�� ��ϵǾ��ִ��� Ȯ���ϴ� �Լ�
		bool IsExistKey(int key);

		// �ش� KeyCode�� ����ϴ� �Լ�
		void RegistKeyCode(int key);

		// InputManager�� Initialize�ϴ� �Լ�
		void Init(HWND hWnd);

		// KeyCode���� �Է¿��θ� �ǽð����� ó���ϴ� �Լ�
		void Update();

		// ��ϵǾ��ִ� KeyCode���� ���� �Լ�
		void Clear();

		// �ش� KeyCode�� Press���θ� �����ϴ� �Լ�
		bool IsKeyPress(int _keyCode);

		// �ش� KeyCode�� Up���θ� �����ϴ� �Լ�
		bool IsKeyUp(int _keyCode);

		// �ش� KeyCode�� Down���θ� �����ϴ� �Լ�
		bool IsKeyDown(int _keyCode);

		// ���� ���콺�� ��ǥ���� �����ϴ� �Լ�
		VECTOR2 GetMouseVec2();

		// ������ InputManager�� Release�ϴ� �Լ�
		void Release();

		InputManager();
		~InputManager();
	};
}

