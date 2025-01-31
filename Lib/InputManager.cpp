#include "InputManager.h"


namespace Euneick
{
	InputManager::InputManager()
	{
		m_vecKeyInfo.clear();
	}

	InputManager::~InputManager()
	{
		m_vecKeyInfo.clear();
	}

	bool InputManager::IsExistKey(int key)
	{
		for (auto iter = m_vecKeyInfo.begin(); iter != m_vecKeyInfo.end(); iter++)
		{
			if ((*iter).KeyCode == key)
				return true;
		}

		return false;
	}

	void InputManager::RegistKeyCode(int key)
	{
		if (IsExistKey(key))
			return;
		else
		{
			KEY_INFO _stKeyInfo;
			memset(&_stKeyInfo, 0, sizeof(KEY_INFO));
			_stKeyInfo.KeyCode = key;
			m_vecKeyInfo.push_back(_stKeyInfo);
		}
	}

	void InputManager::Init(HWND hWnd)
	{
		m_hWnd = hWnd;
	}

	void InputManager::Update()
	{
		POINT _ptMouse;
		GetCursorPos(&_ptMouse);
		ScreenToClient(m_hWnd, &_ptMouse);
		m_vec2Mouse.x = (float)_ptMouse.x;
		m_vec2Mouse.y = (float)_ptMouse.y;

		for (auto iter = m_vecKeyInfo.begin(); iter != m_vecKeyInfo.end(); iter++)
		{
			if (GetKeyState((*iter).KeyCode) & 0x8000)
			{
				if ((*iter).KeyPress == false)	// 키 다운
				{
					(*iter).KeyDown = true;
				}
				else
				{
					(*iter).KeyDown = false;
				}

				(*iter).KeyPress = true;
				(*iter).KeyUp = false;
			}
			else
			{
				if ((*iter).KeyPress)			// 키 업
				{
					(*iter).KeyUp = true;
				}
				else
				{
					(*iter).KeyUp = false;
				}

				(*iter).KeyDown = false;
				(*iter).KeyPress = false;
			}
		}
	}

	void InputManager::Clear()
	{
		m_vecKeyInfo.clear();
	}

	bool InputManager::IsKeyPress(int _keyCode)
	{
		for (auto iter = m_vecKeyInfo.begin(); iter != m_vecKeyInfo.end(); iter++)
			if ((*iter).KeyCode == _keyCode)
				return (*iter).KeyPress;

		assert(!("keyCode not regist!!"));
		return false;
	}

	bool InputManager::IsKeyUp(int _keyCode)
	{
		for (auto iter = m_vecKeyInfo.begin(); iter != m_vecKeyInfo.end(); iter++)
			if ((*iter).KeyCode == _keyCode)
				return (*iter).KeyUp;

		assert(!("keyCode not regist!!"));
		return false;
	}

	bool InputManager::IsKeyDown(int _keyCode)
	{
		for (auto iter = m_vecKeyInfo.begin(); iter != m_vecKeyInfo.end(); iter++)
			if ((*iter).KeyCode == _keyCode)
				return (*iter).KeyDown;

		assert(!("keyCode not regist!!"));
		return false;
	}

	VECTOR2 InputManager::GetMouseVec2()
	{
		return m_vec2Mouse;
	}

	void InputManager::Release()
	{
		m_vecKeyInfo.clear();
	}
}