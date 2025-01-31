#include "Cloud.h"
#include "ClientDefines.h"


Cloud::Cloud()
{
}


Cloud::~Cloud()
{
}

void Cloud::Init()
{
	m_pCloud = EEObjectManager::GetInstance()->CreateImage("Airplane_cloud0.bmp", Z_ORDER_CLOUD);
	for (int i = 1; i < CLOUD_FRAME_MAX; i++)
		m_pCloud->RegistBitMapFrame("Airplane_cloud" + std::to_string(i) + ".bmp");

	int _rand = rand() % CLOUD_FRAME_MAX;
	m_pCloud->SetBitMapFrame(_rand);

	int _iPosX = (rand() % GAME_SCREEN_WIDTH) + GAME_SCREEN_X;
	int _iPosY = (rand() % GAME_SCREEN_HEIGHT) + GAME_SCREEN_Y;

	m_pCloud->SetPosition(VECTOR2((float)_iPosX, (float)_iPosY));

	m_fCloudSizeCY = m_pCloud->GetObjectSize().cy;
	m_fRespawnY = GAME_SCREEN_Y - m_fCloudSizeCY;
	m_fMoveToY = GAME_SCREEN_HEIGHT + m_fCloudSizeCY;
}

void Cloud::Update(float _fElapseTime)
{
	if (!m_pCloud->IsMoveToAction())
	{
		int _iPosX = (rand() % GAME_SCREEN_WIDTH) + GAME_SCREEN_X;

		m_pCloud->SetPosition(VECTOR2((float)_iPosX, m_fRespawnY));

		int _iMoveSpeed = (rand() % 100) + 20;
		m_pCloud->SetMoveTo((float)_iMoveSpeed, VECTOR2((float)_iPosX, m_fMoveToY));
	}
}

void Cloud::OperMove()
{
	int _iMoveSpeed = (rand() % 100) + 20;
	m_pCloud->SetMoveTo((float)_iMoveSpeed, VECTOR2(m_pCloud->GetPosition().x, m_fMoveToY));
}

void Cloud::Draw(HDC hdc)
{
}

void Cloud::Release()
{
}
