#include "pch.h"
#include "EnchantCard.h"
#include "Collider.h"
#include "SceneManager.h"

EnchantCard::EnchantCard()
{
    AddComponent<Collider>()->SetSize({200, 300});
    isHovered = false;
    hoverScale = 1.0f;
}

EnchantCard::~EnchantCard()
{
}

void EnchantCard::Update()
{
}

void EnchantCard::Render(HDC _hdc)
{
    Vec2 pos = GetPos();
    Vec2 size = GetSize();
    Vec2 scaledSize = size * hoverScale;

    PenType borderColor = isHovered ? PenType::RED : PenType::GREEN;

    RECT_RENDER(_hdc, pos.x, pos.y, scaledSize.x, scaledSize.y);

    RECT rc;
    rc.left = (LONG)(pos.x - scaledSize.x / 2);
    rc.top = (LONG)(pos.y - scaledSize.y / 2);
    rc.right = (LONG)(pos.x + scaledSize.x / 2);
    rc.bottom = (LONG)(pos.y + scaledSize.y / 2);

    GDISelector namefont(_hdc, FontType::TITLE);
    DrawText(_hdc, name.c_str(), -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    RECT rc2 = rc;
    rc2.top += 50;
    GDISelector descfont(_hdc, FontType::UI);
    DrawText(_hdc, desc.c_str(), -1, &rc2, DT_CENTER | DT_WORDBREAK);

    GDISelector pen(_hdc, borderColor);
    GDISelector brush(_hdc, BrushType::HOLLOW);
    RECT_RENDER(_hdc, pos.x, pos.y, scaledSize.x, scaledSize.y);
}

void EnchantCard::EnterCollision(Collider* _other)
{
    cout << "Enter";
    isHovered = true;
    hoverScale = 1.1f;
    
}

void EnchantCard::StayCollision(Collider* _other)
{
    cout << "Stay";
    isHovered = true;
}

void EnchantCard::ExitCollision(Collider* _other)
{
    cout << "Exit";
    isHovered = false;
    hoverScale = 1.0f;
    
}

void EnchantCard::SetInfo(const wchar_t* name, const wchar_t* desc)
{
    this->name = name;
    this->desc = desc;
}
