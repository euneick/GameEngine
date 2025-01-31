#include "VECTOR2.h"
#include <math.h>

namespace Euneick
{
	VECTOR2::VECTOR2()
	{
	}

	VECTOR2::VECTOR2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	VECTOR2::~VECTOR2()
	{
	}

	void VECTOR2::operator=(const VECTOR2 &ref)
	{
		x = ref.x;
		y = ref.y;
	}

	VECTOR2 VECTOR2::operator+(const VECTOR2 &ref)
	{
		VECTOR2 _vec2;

		_vec2.x = x + ref.x;
		_vec2.y = y + ref.y;

		return _vec2;
	}

	VECTOR2 VECTOR2::operator-(const VECTOR2 &ref)
	{
		VECTOR2 _vec2;

		_vec2.x = x - ref.x;
		_vec2.y = y - ref.y;

		return _vec2;
	}

	bool VECTOR2::operator==(const VECTOR2 &ref)
	{
		if (x == ref.x && y == ref.y)
			return true;

		return false;
	}

	void VECTOR2::Normalize()
	{
		float n = x * x + y * y;
		// Already normalized.
		if (n == 1.0f)
			return;

		n = sqrt(n);
		// Too close to zero.
		if (n < MATH_TOLERANCE)
			return;

		n = 1.0f / n;
		x *= n;
		y *= n;
	}


	RECT::RECT()
	{
	}

	RECT::RECT(float _left, float _top, float _right, float _bottom)
	{
		left = _left;		top = _top;		right = _right;		bottom = _bottom;
	}

	RECT::~RECT()
	{
	}

	void RECT::operator= (const RECT &ref)
	{
		left = ref.left;
		right = ref.right;
		top = ref.top;
		bottom = ref.bottom;
	}

	bool RECT::IsCollision(RECT& other)
	{
		if (left <= other.right && top <= other.bottom &&  right >= other.left &&  bottom >= other.top)
			return true;

		return false;
	}

	bool RECT::IsVec2InRect(VECTOR2& vec2)
	{
		if (left <= vec2.x && vec2.x <= right &&
			top <= vec2.y && vec2.y <= bottom)
			return true;

		return false;
	}

	::RECT RECT::GetWinRECT()
	{
		::RECT rc = { left , top , right , bottom };
		return rc;
	}


	EERGB::EERGB()
	{
	}

	EERGB::EERGB(int _r, int _g, int  _b)
	{
		r = _r;		g = _g;		b = _b;
	}

	EERGB::~EERGB()
	{
	}

	void EERGB::operator= (const EERGB &ref)
	{
		r = ref.r;
		g = ref.g;
		b = ref.b;
	}
}

