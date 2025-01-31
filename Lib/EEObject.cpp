#include "EEObject.h"
#include "EEObjectManager.h"


namespace Euneick
{
	EEObject::EEObject()
	{
	}


	EEObject::~EEObject()
	{
	}
	
	void EEObject::SetObjectRect()
	{
		m_rcRect = RECT(m_vec2Position.x - (m_size.cx * (m_vec2AnchorPoint.x) * m_vec2Scale.x),
			m_vec2Position.y - (m_size.cy * (m_vec2AnchorPoint.y) * m_vec2Scale.y),
			m_vec2Position.x + (m_size.cx * (1 - m_vec2AnchorPoint.x) * m_vec2Scale.x),
			m_vec2Position.y + (m_size.cy * (1 - m_vec2AnchorPoint.y) * m_vec2Scale.y));
	}

	void EEObject::ResetComponent()
	{
		m_vec2Position = VECTOR2(0.0f, 0.0f);
		m_vec2AnchorPoint = VECTOR2(0.5f, 0.5f);
		m_vec2Scale = VECTOR2(1.0f, 1.0f);
	}

	void EEObject::SetAnchorPoint(VECTOR2 _vec2)
	{
		m_vec2AnchorPoint = _vec2;
		SetObjectRect();
	}

	VECTOR2 EEObject::GetAnchorPoint()
	{
		return m_vec2AnchorPoint;
	}

	void EEObject::SetPosition(VECTOR2 _vec2)
	{
		m_vec2Position = _vec2;
		SetObjectRect();
	}

	VECTOR2 EEObject::GetPosition()
	{
		return m_vec2Position;
	}

	void EEObject::SetScale(VECTOR2 _vec2)
	{
		m_vec2Scale = _vec2;
		SetObjectRect();
	}

	VECTOR2 EEObject::GetScale()
	{
		return m_vec2Scale;
	}

	void EEObject::SetZOrder(int _iZOrder)
	{
		int _iPrevZOrder = m_iZOrder;

		EEObjectManager::GetInstance()->OperChangeZOrder(_iPrevZOrder, _iZOrder, this);

		m_iZOrder = _iZOrder;
	}
}
