#pragma once
#include "GlobalDefines.h"

namespace Euneick
{
	class VECTOR2;
	/**
	*	@brief		: BitMap 클래스
	*	@details	: BitMap파일의 데이터를 받아와서 Parsing하고, 이를 그리는 클래스
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class BitMap
	{
	private:
		HDC			m_hMemDC;
		HBITMAP		m_hBitMap;
		HBITMAP		m_hOldBitMap;
		SIZE		m_size;

	public:
		// Back Buffer를 Initialize 하는 함수
		void InitBackBuf(HDC hdc, int x, int y);

		// 해당 파일이름의 BitMap파일을 Initialize하는 함수
		void Init(HDC hdc, string _strFileName);

		// Initialize된 BitMap을 화면에 그리는 함수
		void Draw(VECTOR2 _vec2Pos, VECTOR2  _vec2Anchor, VECTOR2  _vec2Scale);

		// 생성된 BitMap을 Release하는 함수
		void Release();

		// BackBuffer를 그리는 함수
		void DrawBackBuf(HDC hdc);

		// BitMap의 HDC를 반환하는 함수
		HDC GetDC();

		// BitMap의 Size를 반환하는 함수
		inline SIZE GetBitMapSize()
		{
			return m_size;
		}

		BitMap();
		~BitMap();
	};
}