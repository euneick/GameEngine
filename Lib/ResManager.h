#pragma once
#include "GlobalDefines.h"

namespace Euneick
{
	class BitMap;
	/**
	*	@brief		: BitMap들을 관리하는 클래스
	*	@details	: 생성된 BitMap들을 관리하고 원하는 BitMap을 리턴하는 클래스
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class ResManager : public SingleTon<ResManager>
	{
	private:
		BitMap*					m_pBackBuf;
		map<string, BitMap*>	m_mapBitMap;

		// 등록되어있지 않은 BitMap을 Initalize하는 함수
		BitMap* InitBitMap(string _strFileName);

	public:
		// 등록되어있는 BitMap을 Return하는 함수
		BitMap* GetBitMap(string _strFileName);

		// 생성된 ResManager를 Release하는 함수
		void Release();

		// BackBuffer를 Initialize 하는 함수
		void InitBackBuf(HDC hdc, int x, int y);

		// BackBuffer를 그리는 함수
		void DrawBackBuf(HDC hdc);

		// BackBuffer의 HDC를 리턴하는 함수
		HDC GetBackBufDC();

		ResManager();
		~ResManager();
	};
}

