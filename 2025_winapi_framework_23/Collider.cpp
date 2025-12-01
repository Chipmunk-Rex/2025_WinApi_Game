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
	// initialize cached world position
	m_worldPos = GetOwner()->GetPos() + m_offsetPos;
}

void Collider::LateUpdate()
{
	Object* owner = GetOwner();
	m_worldPos = owner->GetPos() + m_offsetPos;
}

void Collider::Render(HDC _hdc)
{
#ifdef _DEBUG
	PenType penColor = PenType::GREEN;
	if (m_showDebug)
		penColor = PenType::RED;
	// �簢��
	GDISelector pen(_hdc, penColor);
	GDISelector brush(_hdc, BrushType::HOLLOW);
	const Vec2& worldPos = GetWorldPos();
	RECT_RENDER(_hdc, worldPos.x, worldPos.y, m_size.x ,m_size.y);
#endif
}

void Collider::EnterCollision(Collider* _other, const CollisionInfo& collisionInfo)
{
	m_showDebug = true;
	GetOwner()->EnterCollision(_other);
	m_collisionInfos.push_back(collisionInfo);
}

void Collider::StayCollision(Collider* _other)
{
	GetOwner()->StayCollision(_other);
}

void Collider::ExitCollision(Collider* _other, const CollisionInfo& collisionInfo)
{
	m_showDebug = false;
	GetOwner()->ExitCollision(_other);
	auto it = std::find(m_collisionInfos.begin(), m_collisionInfos.end(), collisionInfo);
	if (it != m_collisionInfos.end())
	{
		m_collisionInfos.erase(it);
	}
}
