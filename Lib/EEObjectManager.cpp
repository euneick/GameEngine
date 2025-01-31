#include "EEObjectManager.h"
#include "EEObject.h"
#include "EEImage.h"
#include "EEButton.h"
#include "EELabel.h"
#include "EEProgressbar.h"


namespace Euneick
{
	EEObjectManager::EEObjectManager()
	{
	}

	EEObjectManager::~EEObjectManager()
	{
	}

	void EEObjectManager::Init()
	{
	}

	EEImage* EEObjectManager::CreateImage(string _strFileName, int _iZOrder)
	{
		EEImage* _pNew = new EEImage();
		_pNew->Create(_strFileName, _iZOrder);

		RegistEEObject(_pNew, _iZOrder);

		return _pNew;
	}

	EEButton* EEObjectManager::CreateButton(string _strFileName, int _iZOrder)
	{
		EEButton* _pNew = new EEButton();
		_pNew->Create(_strFileName, _iZOrder);

		RegistEEObject(_pNew, _iZOrder);

		return _pNew;
	}

	EELabel* EEObjectManager::CreateLabel(string _strText, int _iZOrder)
	{
		EELabel* _pNew = new EELabel();
		_pNew->Create(_strText, _iZOrder);

		RegistEEObject(_pNew, _iZOrder);

		return _pNew;
	}

	EEProgressbar* EEObjectManager::CreateProgressBar(string _strText, int _iZOrder)
	{
		EEProgressbar* _pNew = new EEProgressbar();
		_pNew->Create(_strText, _iZOrder);

		RegistEEObject(_pNew, _iZOrder);

		return _pNew;
	}

	EEProgressbar* EEObjectManager::CreateProgressBar(string _strLeft, string _strCenter, string _strRight, int _iZOrder)
	{
		EEProgressbar* _pNew = new EEProgressbar();
		_pNew->Create(_strCenter, _iZOrder);
		_pNew->AddLeftRightBar(_strLeft, _strRight);

		RegistEEObject(_pNew, _iZOrder);

		return _pNew;
	}

	void EEObjectManager::RegistEEObject(EEObject* _pNew, int _iZOrder)
	{
		auto iter = m_mapObjects.find(_iZOrder);

		if (iter == m_mapObjects.end())
		{
			vector<EEObject*>* _pNewVec = new vector<EEObject*>();
			_pNewVec->push_back(_pNew);

			m_mapObjects.insert(make_pair(_iZOrder, _pNewVec));
		}
		else
		{
			iter->second->push_back(_pNew);
		}
	}

	void EEObjectManager::OperChangeZOrder(int _iPrevZOrder, int _iCurZOrder, EEObject* _pObject)
	{
		auto iterMap = m_mapObjects.find(_iPrevZOrder);

		for (auto iter = iterMap->second->begin(); iter != iterMap->second->end(); iter++)
		{
			if (*iter == _pObject)
			{
				iterMap->second->erase(iter);
				break;
			}
		}

		auto iterMap2 = m_mapObjects.find(_iCurZOrder);

		if (iterMap2 == m_mapObjects.end())
		{
			vector<EEObject*>* _pNewVec = new vector<EEObject*>();
			_pNewVec->push_back(_pObject);

			m_mapObjects.insert(make_pair(_iCurZOrder, _pNewVec));
		}
		else
		{
			iterMap2->second->push_back(_pObject);
		}
	}

	void EEObjectManager::Update(float _fElapseTime)
	{
		for (auto iterMap = m_mapObjects.begin(); iterMap != m_mapObjects.end(); iterMap++)
		{
			for(auto iterVec = iterMap->second->begin();iterVec!= iterMap->second->end();iterVec++)
			{
				(*iterVec)->Update(_fElapseTime);
			}
		}
	}

	void EEObjectManager::Draw()
	{
		for (auto iterMap = m_mapObjects.begin(); iterMap != m_mapObjects.end(); iterMap++)
		{
			for (auto iterVec = iterMap->second->begin(); iterVec != iterMap->second->end(); iterVec++)
			{
				(*iterVec)->Draw();
			}
		}
	}

	void EEObjectManager::Release()
	{
		for (auto iterMap = m_mapObjects.begin(); iterMap != m_mapObjects.end(); iterMap++)
		{
			for (auto iterVec = iterMap->second->begin(); iterVec != iterMap->second->end(); iterVec++)
			{
				(*iterVec)->Release();
				SAFE_DELETE(*iterVec);
			}
			iterMap->second->clear();
			SAFE_DELETE(iterMap->second);
		}
		m_mapObjects.clear();
	}
}
