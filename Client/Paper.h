#pragma once
#include "EngineDefine.h"

USING_NS_EE;

enum PAPER_STATE
{
	PAPER_STATE_BLUE,
	PAPER_STATE_RED,
	PAPER_STATE_GREEN,
	PAPER_STATE_YELLOW,
	PAPER_STATE_END
};

class Paper
{
private:
	EEImage* m_pPaperImage;

	VECTOR2 m_vec2Center;

	PAPER_STATE m_ePaperState;

public:
	void Init(VECTOR2 _vec2Center);
	void Update(float _fElapseTime);
	void Release();

	void OperCorrectAction();
	void OperWrongAction();
	void SetPaperCenter();
	void SetPaperZOrder(int _iZOrder);

	inline PAPER_STATE GetPaperState()
	{
		return m_ePaperState;
	}

	Paper();
	~Paper();
};

