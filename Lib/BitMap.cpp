#include "BitMap.h"
#include "VECTOR2.h"
#include "ResManager.h"

namespace Euneick
{
	BitMap::BitMap()
	{
	}


	BitMap::~BitMap()
	{
	}

	void BitMap::InitBackBuf(HDC hdc, int x, int y)
	{
		m_hMemDC = CreateCompatibleDC(hdc);
		m_hBitMap = CreateCompatibleBitmap(hdc, x, y);
		m_hOldBitMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);

		m_size.cx = x;
		m_size.cy = y;
	}

	void BitMap::Init(HDC hdc, string _strFileName)
	{
		string _str = "Resource\\" + _strFileName;

		m_hMemDC = CreateCompatibleDC(hdc);
		m_hBitMap = (HBITMAP)LoadImage(NULL, _str.c_str(), IMAGE_BITMAP, 0, 0,
			LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		m_hOldBitMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);

		//비트맵의 WIDTH HEIGHT를 받아오는 매크로
		BITMAP bmp_info;
		GetObject(m_hBitMap, sizeof(bmp_info), &bmp_info);
		m_size.cx = (int)bmp_info.bmWidth;
		m_size.cy = (int)bmp_info.bmHeight;
	}

	void BitMap::Draw(VECTOR2 _vec2Pos, VECTOR2  _vec2Anchor, VECTOR2  _vec2Scale)
	{
		TransparentBlt(
			ResManager::GetInstance()->GetBackBufDC(),
			(int)(_vec2Pos.x - (m_size.cx * _vec2Anchor.x * _vec2Scale.x)),
			(int)(_vec2Pos.y - (m_size.cy * _vec2Anchor.y * _vec2Scale.y)),
			(int)(m_size.cx * _vec2Scale.x),
			(int)(m_size.cy * _vec2Scale.y),
			m_hMemDC, 0, 0, m_size.cx, m_size.cy, RGB(255, 0, 255)
		);
	}

	void BitMap::DrawBackBuf(HDC hdc)
	{
		BitBlt(hdc, 0, 0, m_size.cx, m_size.cy, m_hMemDC, 0, 0, SRCCOPY);
	}

	HDC BitMap::GetDC()
	{
		return m_hMemDC;
	}

	void BitMap::Release()
	{
		SelectObject(m_hMemDC, m_hOldBitMap);
		DeleteObject(m_hBitMap);
		DeleteDC(m_hMemDC);
	}
}