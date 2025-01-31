#pragma once
#include "EngineDefine.h"

USING_NS_EE;

class PaperStar
{
private:
	EEImage* m_pStarImage;
	EELabel* m_pStarLabel;

public:
	void Init(VECTOR2 _vec2Center);
	void Release();

	void SetPaperVisibility(bool _b);
	void OperChangeScoreLabel(int _iScore);

	PaperStar();
	~PaperStar();
};

