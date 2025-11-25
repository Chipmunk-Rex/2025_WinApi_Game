#include "pch.h"
#include "EnchantCard.h"
#include "Collider.h"
#include "SceneManager.h"
#include "InputManager.h"

EnchantCard::EnchantCard()
{
    AddComponent<Collider>()->SetSize({ 200, 300 });
    isHovered = false;
    targetScale = 1;
    hoverScale = 0;
}

EnchantCard::~EnchantCard()
{
}

void EnchantCard::Update()
{
    float timee = 5.0f * fDT;
    hoverScale = hoverScale + (targetScale - hoverScale) * timee;

    if (GET_KEYDOWN(KEY_TYPE::LBUTTON) && isHovered)
    {
        targetScale = 0;
        hoverScale = 0;
       
    }
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

    RECT nameRc = rc;
    nameRc.left = (LONG)(pos.x - scaledSize.x / 2);
    nameRc.top = (LONG)(pos.y - scaledSize.y / 2);
    nameRc.right = (LONG)(pos.x + scaledSize.x / 2);
    nameRc.bottom = (LONG)(pos.y + scaledSize.y / 2) - 50;

    GDISelector namefont(_hdc, FontType::TITLE);
    DrawText(_hdc, name.c_str(), -1, &nameRc, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);

    RECT descRc = rc;
    descRc.top += 50;
    GDISelector descfont(_hdc, FontType::UI);
    DrawText(_hdc, desc.c_str(), -1, &descRc, DT_CENTER | DT_BOTTOM | DT_WORDBREAK);

    GDISelector pen(_hdc, borderColor);
    GDISelector brush(_hdc, BrushType::HOLLOW);
    RECT_RENDER(_hdc, pos.x, pos.y, scaledSize.x, scaledSize.y);
}

void EnchantCard::EnterCollision(Collider* _other)
{
    isHovered = true;
    targetScale = 1.1f;
}

void EnchantCard::StayCollision(Collider* _other)
{
    isHovered = true;
    targetScale = 1.1f;
}

void EnchantCard::ExitCollision(Collider* _other)
{
    isHovered = false;
    targetScale = 1.0f;
}

void EnchantCard::SetInfo(const wchar_t* name, const wchar_t* desc)
{
    this->name = name;
    this->desc = desc;
}
