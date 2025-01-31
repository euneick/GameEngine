#pragma once
#include "GlobalDefines.h"

namespace Euneick
{
	class EEObject;
	class EEImage;
	class EEButton;
	class EELabel;
	class EEProgressbar;
	/**
	*	@brief		: EEOjbect를 관리하는 클래스
	*	@details	: 생성된 EEOjbect들을 실시간 호출하고 그리는 클래스
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class EEObjectManager : public SingleTon<EEObjectManager>
	{
	private:
		map<int, vector<EEObject*>*> m_mapObjects;

		// EEObject를 풀에 등록하는 함수
		void RegistEEObject(EEObject* _pNew, int _iZOrder);

	public:
		// EEObject 풀을 생성하는 함수
		void Init();

		// EEImage를 생성하는 함수
		EEImage* CreateImage(string _strFileName, int _iZOrder);

		// EEButton을 생성하는 함수
		EEButton* CreateButton(string _strFileName, int _iZOrder);

		// EELabel을 생성하는 함수
		EELabel* CreateLabel(string _strText, int _iZOrder);

		// 양쪽 이미지가 없는 EEProgressBar를 생성하는 함수
		EEProgressbar* CreateProgressBar(string _strText, int _iZOrder);

		// 양쪽 이미지가 있는 EEProgressBar를 생성하는 함수
		EEProgressbar* CreateProgressBar(string _strLeft, string _strCenter, string _strRight, int _iZOrder);

		// EEObject의 ZOreder를 변경하는 함수
		void OperChangeZOrder(int _iPrevZOrder, int _iCurZOrder, EEObject* _pObject);

		// EEObject들의 실시간 호출 함수
		void Update(float _fElapseTime);

		// EEObject를 그리는 함수
		void Draw();

		// EEObject들의 메모리 해제 함수
		void Release();

		EEObjectManager();
		~EEObjectManager();
	};
}

