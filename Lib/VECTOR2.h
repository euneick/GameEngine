#pragma once
#include <Windows.h>

#define MATH_TOLERANCE 2e-37f

namespace Euneick
{
	/**
	*	@brief		: 2���� ��ǥ�� float������ �������ִ� Ŭ����
	*	@details	: 2���� ��ǥ�� float������ �������ִ� Ŭ����
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class VECTOR2
	{
	public:
		float	x;
		float	y;

		// = ��ȣ ������ �Լ�
		void operator=(const VECTOR2 &ref);

		// + ��ȣ ������ �Լ�
		VECTOR2 operator+(const VECTOR2 &ref);

		// - ��ȣ ������ �Լ�
		VECTOR2 operator-(const VECTOR2 &ref);

		// == ��ȣ ������ �Լ�
		bool operator==(const VECTOR2 &ref);

		// ������ ����ȭ
		void Normalize();

		VECTOR2();
		VECTOR2(float _x, float _y);
		~VECTOR2();
	};

	/**
	*	@brief		: Rect�� float������ �������ִ� Ŭ����
	*	@details	: Rect�� float������ �������ִ� Ŭ����
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class RECT
	{
	public:
		float	left;
		float	top;
		float	right;
		float	bottom;

		// �� RECT ���� �浹 üũ���θ� ��ȯ�ϴ� �Լ�
		bool IsCollision(RECT& other);

		// RECT�ȿ� VECTOR2�� �ִ��� ��ȯ�ϴ� �Լ�
		bool IsVec2InRect(VECTOR2& vec2);

		// = ��ȣ�� ���� �����ϴ� �Լ�
		void operator= (const RECT &ref);

		// ������ RECT�� Window RECT�� ��ȯ�ϴ� �Լ�
		::RECT GetWinRECT();

		RECT();
		RECT(float _left, float _top, float _right, float _bottom);
		~RECT();
	};

	/**
	*	@brief		: RGB���� int������ ������ �ִ� Ŭ����
	*	@details	: RGB���� int������ ������ �ִ� Ŭ����
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class EERGB
	{
	public :
		int r;
		int g;
		int b;

		// = ��ȣ�� ���� �����ϴ� �Լ�
		void operator= (const EERGB &ref);

		EERGB();
		EERGB(int _r, int _g, int  _b);
		~EERGB();
	};
}

