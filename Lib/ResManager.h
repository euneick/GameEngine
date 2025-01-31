#pragma once
#include "GlobalDefines.h"

namespace Euneick
{
	class BitMap;
	/**
	*	@brief		: BitMap���� �����ϴ� Ŭ����
	*	@details	: ������ BitMap���� �����ϰ� ���ϴ� BitMap�� �����ϴ� Ŭ����
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class ResManager : public SingleTon<ResManager>
	{
	private:
		BitMap*					m_pBackBuf;
		map<string, BitMap*>	m_mapBitMap;

		// ��ϵǾ����� ���� BitMap�� Initalize�ϴ� �Լ�
		BitMap* InitBitMap(string _strFileName);

	public:
		// ��ϵǾ��ִ� BitMap�� Return�ϴ� �Լ�
		BitMap* GetBitMap(string _strFileName);

		// ������ ResManager�� Release�ϴ� �Լ�
		void Release();

		// BackBuffer�� Initialize �ϴ� �Լ�
		void InitBackBuf(HDC hdc, int x, int y);

		// BackBuffer�� �׸��� �Լ�
		void DrawBackBuf(HDC hdc);

		// BackBuffer�� HDC�� �����ϴ� �Լ�
		HDC GetBackBufDC();

		ResManager();
		~ResManager();
	};
}

