#pragma once
#include "GlobalDefines.h"
#include "VECTOR2.h"

namespace Euneick
{
	/**
	*	@brief		: Input 데이터를 관리하는 클래스
	*	@details	: 마우스, 키보드의 데이터를 등록하고, 이를 관리하는 클래스
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
		// 해당 KeyCode가 등록되어있는지 확인하는 함수
		bool IsExistKey(int key);

		// 해당 KeyCode를 등록하는 함수
		void RegistKeyCode(int key);

		// InputManager를 Initialize하는 함수
		void Init(HWND hWnd);

		// KeyCode들의 입력여부를 실시간으로 처리하는 함수
		void Update();

		// 등록되어있는 KeyCode들을 비우는 함수
		void Clear();

		// 해당 KeyCode의 Press여부를 리턴하는 함수
		bool IsKeyPress(int _keyCode);

		// 해당 KeyCode의 Up여부를 리턴하는 함수
		bool IsKeyUp(int _keyCode);

		// 해당 KeyCode의 Down여부를 리턴하는 함수
		bool IsKeyDown(int _keyCode);

		// 현재 마우스의 좌표값을 리턴하는 함수
		VECTOR2 GetMouseVec2();

		// 생성된 InputManager를 Release하는 함수
		void Release();

		InputManager();
		~InputManager();
	};
}

