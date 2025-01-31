#pragma once
#include <Windows.h>

#define MATH_TOLERANCE 2e-37f

namespace Euneick
{
	/**
	*	@brief		: 2차원 좌표를 float형으로 가지고있는 클래스
	*	@details	: 2차원 좌표를 float형으로 가지고있는 클래스
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class VECTOR2
	{
	public:
		float	x;
		float	y;

		// = 기호 재정의 함수
		void operator=(const VECTOR2 &ref);

		// + 기호 재정의 함수
		VECTOR2 operator+(const VECTOR2 &ref);

		// - 기호 재정의 함수
		VECTOR2 operator-(const VECTOR2 &ref);

		// == 기호 재정의 함수
		bool operator==(const VECTOR2 &ref);

		// 벡터의 정규화
		void Normalize();

		VECTOR2();
		VECTOR2(float _x, float _y);
		~VECTOR2();
	};

	/**
	*	@brief		: Rect를 float형으로 가지고있는 클래스
	*	@details	: Rect를 float형으로 가지고있는 클래스
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

		// 두 RECT 간의 충돌 체크여부를 반환하는 함수
		bool IsCollision(RECT& other);

		// RECT안에 VECTOR2가 있는지 반환하는 함수
		bool IsVec2InRect(VECTOR2& vec2);

		// = 기호로 값을 대입하는 함수
		void operator= (const RECT &ref);

		// 재정의 RECT를 Window RECT로 변환하는 함수
		::RECT GetWinRECT();

		RECT();
		RECT(float _left, float _top, float _right, float _bottom);
		~RECT();
	};

	/**
	*	@brief		: RGB값을 int형으로 가지고 있는 클래스
	*	@details	: RGB값을 int형으로 가지고 있는 클래스
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

		// = 기호로 값을 대입하는 함수
		void operator= (const EERGB &ref);

		EERGB();
		EERGB(int _r, int _g, int  _b);
		~EERGB();
	};
}

