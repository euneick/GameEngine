#include "ResManager.h"
#include "BitMap.h"

namespace Euneick
{
	ResManager::ResManager()
	{
	}


	ResManager::~ResManager()
	{
		m_pBackBuf->Release();
		SAFE_DELETE(m_pBackBuf);

		for (auto iter = m_mapBitMap.begin(); iter != m_mapBitMap.end(); iter++)
		{
			auto del = (*iter).second;
			SAFE_DELETE(del);
		}
		m_mapBitMap.clear();
	}

	BitMap* ResManager::InitBitMap(string _strFileName)
	{
		auto iter = m_mapBitMap.find(_strFileName);

		if (iter == m_mapBitMap.end())
		{
			BitMap* _pBitmap = new BitMap();
			_pBitmap->Init(m_pBackBuf->GetDC(), _strFileName);

			m_mapBitMap.insert(make_pair(_strFileName, _pBitmap));
			return _pBitmap;
		}
		else
			return iter->second;
	}

	void ResManager::InitBackBuf(HDC hdc, int x, int y)
	{
		m_pBackBuf = new BitMap();
		m_pBackBuf->InitBackBuf(hdc, x, y);
	}

	void ResManager::DrawBackBuf(HDC hdc)
	{
		m_pBackBuf->DrawBackBuf(hdc);
	}

	HDC ResManager::GetBackBufDC()
	{
		return m_pBackBuf->GetDC();
	}

	BitMap* ResManager::GetBitMap(string _strFileName)
	{
		auto iter = m_mapBitMap.find(_strFileName);

		if (iter != m_mapBitMap.end())
			return iter->second;
		else
			return InitBitMap(_strFileName);
	}

	void ResManager::Release()
	{
		for (auto iter = m_mapBitMap.begin(); iter != m_mapBitMap.end(); iter++)
		{
			iter->second->Release();
			auto del = (*iter).second;
			SAFE_DELETE(del);
		}
		m_mapBitMap.clear();
	}
}