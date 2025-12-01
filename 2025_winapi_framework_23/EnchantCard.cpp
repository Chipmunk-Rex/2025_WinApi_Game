#include "pch.h"
#include "EnchantCard.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "CardManager.h"

EnchantCard::EnchantCard()
{
    isHovered = false;
    wasHovered = false;

    targetScale = 1;
    hoverScale = 0;
}

EnchantCard::~EnchantCard()
{
}

void EnchantCard::Update()
{
    Vec2 mouse = GET_SINGLE(InputManager)->GetMousePos();
    Vec2 pos = GetPos();
    Vec2 size = GetSize();

    bool inside =
        mouse.x >= pos.x - size.x * 0.5f &&
        mouse.x <= pos.x + size.x * 0.5f &&
        mouse.y >= pos.y - size.y * 0.5f &&
        mouse.y <= pos.y + size.y * 0.5f;

    if (inside && !wasHovered)
    {
        isHovered = true;
        targetScale = 1.1f;
        cout << "enter\n";
    }

    if (!inside && wasHovered)
    {
        isHovered = false;
        targetScale = 1.0f;
        cout << "exit\n";
    }

    wasHovered = inside;

    if (inside && GET_SINGLE(InputManager)->IsDown(KEY_TYPE::LBUTTON))
    {
        OnClick();
    }

    float t = 5.0f * fDT;
    hoverScale += (targetScale - hoverScale) * t;
}

void EnchantCard::Render(HDC _hdc)
{
    Vec2 pos = GetPos();
    Vec2 size = GetSize();

    Vec2 scaled = size * hoverScale;

    RECT rc;
    rc.left = (LONG)(pos.x - scaled.x * 0.5f);
    rc.top = (LONG)(pos.y - scaled.y * 0.5f);
    rc.right = (LONG)(pos.x + scaled.x * 0.5f);
    rc.bottom = (LONG)(pos.y + scaled.y * 0.5f);

    PenType borderColor = isHovered ? PenType::RED : PenType::GREEN;

    GDISelector pen(_hdc, borderColor);
    GDISelector brush(_hdc, BrushType::HOLLOW);
    Rectangle(_hdc, rc.left, rc.top, rc.right, rc.bottom);

    TransparentBlt(
        _hdc,
        rc.left,
        rc.top,
        (int)scaled.x,
        (int)scaled.y,
        itemTex->GetTextureDC(),
        0, 0,
        itemTex->GetWidth(),
        itemTex->GetHeight(),
        RGB(255, 0, 255)
    );

    RECT nameRc = rc;
    nameRc.bottom -= 50;
    GDISelector namefont(_hdc, FontType::TITLE);
    DrawText(_hdc, name.c_str(), -1, &nameRc, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);

    RECT descRc = rc;
    descRc.top += 50;
    GDISelector descfont(_hdc, FontType::UI);
    DrawText(_hdc, desc.c_str(), -1, &descRc, DT_CENTER | DT_BOTTOM | DT_WORDBREAK);
}

void EnchantCard::OnClick()
{
    GET_SINGLE(CardManager)->ClearCards();

    targetScale = 0;
    hoverScale = 0;
}

void EnchantCard::DisappearCard()
{
    targetScale = 0;
    hoverScale = 0;
}

void EnchantCard::SetInfo(const wchar_t* name, const wchar_t* desc, const wchar_t* fileName)
{
    this->name = name;
    this->desc = desc;
    this->fileName = fileName;
    itemTex = GET_SINGLE(ResourceManager)->GetTexture(fileName);
}
