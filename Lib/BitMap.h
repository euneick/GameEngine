#pragma once
#include "GlobalDefines.h"

namespace Euneick
{
	class VECTOR2;
	/**
	*	@brief		: BitMap Ŭ����
	*	@details	: BitMap������ �����͸� �޾ƿͼ� Parsing�ϰ�, �̸� �׸��� Ŭ����
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
		// Back Buffer�� Initialize �ϴ� �Լ�
		void InitBackBuf(HDC hdc, int x, int y);

		// �ش� �����̸��� BitMap������ Initialize�ϴ� �Լ�
		void Init(HDC hdc, string _strFileName);

		// Initialize�� BitMap�� ȭ�鿡 �׸��� �Լ�
		void Draw(VECTOR2 _vec2Pos, VECTOR2  _vec2Anchor, VECTOR2  _vec2Scale);

		// ������ BitMap�� Release�ϴ� �Լ�
		void Release();

		// BackBuffer�� �׸��� �Լ�
		void DrawBackBuf(HDC hdc);

		// BitMap�� HDC�� ��ȯ�ϴ� �Լ�
		HDC GetDC();

		// BitMap�� Size�� ��ȯ�ϴ� �Լ�
		inline SIZE GetBitMapSize()
		{
			return m_size;
		}

		BitMap();
		~BitMap();
	};
}