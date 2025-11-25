#include "pch.h"
#include "Collider.h"
#include "Object.h"
UINT Collider::m_nextID = 0;
Collider::Collider()
	: m_ID(m_nextID++)
	, m_showDebug(false)
	, m_name{}
	, m_isTrigger(false)
{
}
Collider::~Collider()
{
}
void Collider::Init()
{
	m_size = GetOwner()->GetSize();
	m_offsetPos = { 0.f, 0.f };
}

void Collider::LateUpdate()
{
	Object* owner = GetOwner();
	Vec2 pos = owner->GetPos();
}

void Collider::Render(HDC _hdc)
{
#ifdef _DEBUG
	PenType penColor = PenType::GREEN;
	if (m_showDebug)
		penColor = PenType::RED;
	// »ç°¢Çü
	GDISelector pen(_hdc, penColor);
	GDISelector brush(_hdc, BrushType::HOLLOW);
	Vec2 worldPos = GetWorldPos();
	RECT_RENDER(_hdc, worldPos.x, worldPos.y, m_size.x ,m_size.y);
#endif
}

void Collider::EnterCollision(Collider* _other)
{
	m_showDebug = true;
	GetOwner()->EnterCollision(_other);
}

void Collider::StayCollision(Collider* _other)
{
	GetOwner()->StayCollision(_other);
}

void Collider::ExitCollision(Collider* _other)
{
	m_showDebug = false;
	GetOwner()->ExitCollision(_other);
}
