#pragma once
#include "Component.h"
#include "Object.h"
class Collider :   public Component
{
public:
    Collider();
    ~Collider();
public:
	// Component을(를) 통해 상속됨
	void Init() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;
public:
    void SetSize(Vec2 _size) { m_size = _size; }
    const Vec2& GetSize() const { return m_size; }
    void SetOffSetPos(Vec2 _OffsetPos)
    {
        m_offsetPos = _OffsetPos;
    }
    const Vec2& GetOffSetPos() const { return m_offsetPos; }
    const Vec2& GetWorldPos() const
    {
        return m_worldPos;
    }
    UINT GetID() const { return m_ID; }
    void EnterCollision(Collider* _other);
    void StayCollision(Collider* _other);
    void ExitCollision(Collider* _other);
    void SetName(const wstring& n) { m_name = n; }
    const wstring& GetName() const { return m_name; }

    void SetTrigger(bool t) { m_isTrigger = t; }
    bool IsTrigger() const { return m_isTrigger; }
private:
    Vec2 m_size; // 콜라이더 크기
    // Object로부터 상대적인 위치
    Vec2 m_offsetPos;
    Vec2 m_worldPos; // cached world position
    UINT m_ID; // 충돌체 고유 ID값
    static UINT m_nextID;
    bool m_showDebug;
    wstring m_name;
    bool m_isTrigger;
};

