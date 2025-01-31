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
	*	@brief		: EEOjbect�� �����ϴ� Ŭ����
	*	@details	: ������ EEOjbect���� �ǽð� ȣ���ϰ� �׸��� Ŭ����
	*	@author		: Euneick // eternal_sity@naver.com
	*	@date		: 2018-10-01
	*	@version	: 0.0.1
	*/
	class EEObjectManager : public SingleTon<EEObjectManager>
	{
	private:
		map<int, vector<EEObject*>*> m_mapObjects;

		// EEObject�� Ǯ�� ����ϴ� �Լ�
		void RegistEEObject(EEObject* _pNew, int _iZOrder);

	public:
		// EEObject Ǯ�� �����ϴ� �Լ�
		void Init();

		// EEImage�� �����ϴ� �Լ�
		EEImage* CreateImage(string _strFileName, int _iZOrder);

		// EEButton�� �����ϴ� �Լ�
		EEButton* CreateButton(string _strFileName, int _iZOrder);

		// EELabel�� �����ϴ� �Լ�
		EELabel* CreateLabel(string _strText, int _iZOrder);

		// ���� �̹����� ���� EEProgressBar�� �����ϴ� �Լ�
		EEProgressbar* CreateProgressBar(string _strText, int _iZOrder);

		// ���� �̹����� �ִ� EEProgressBar�� �����ϴ� �Լ�
		EEProgressbar* CreateProgressBar(string _strLeft, string _strCenter, string _strRight, int _iZOrder);

		// EEObject�� ZOreder�� �����ϴ� �Լ�
		void OperChangeZOrder(int _iPrevZOrder, int _iCurZOrder, EEObject* _pObject);

		// EEObject���� �ǽð� ȣ�� �Լ�
		void Update(float _fElapseTime);

		// EEObject�� �׸��� �Լ�
		void Draw();

		// EEObject���� �޸� ���� �Լ�
		void Release();

		EEObjectManager();
		~EEObjectManager();
	};
}

