#include "pch.h"
#include "EnchantCard.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "CardManager.h"
#include "PlayerManager.h"
#include "SceneManager.h"
#include "LaserProjectile.h"

EnchantCard::EnchantCard()
{
    isHovered = false;
    wasHovered = false;

    targetScale = 1.f;
    hoverScale = 0.f;

    destroyDelay = -1;
    waitingDestroy = false;

    
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
    }

    if (!inside && wasHovered)
    {
        isHovered = false;
        targetScale = 1.0f;
    }

    wasHovered = inside;

    if (inside && GET_SINGLE(InputManager)->IsDown(KEY_TYPE::LBUTTON))
        OnClick();
    float t = 15.0f * fDT;
    hoverScale += (targetScale - hoverScale) * t;

    if (waitingDestroy)
    {
        destroyDelay -= fDT;
        if (destroyDelay <= 0.f)
        {
            waitingDestroy = false;
            SetDead();
        }
    }
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
        rc.left, rc.top,
        (int)scaled.x, (int)scaled.y,
        backgroundTex->GetTextureDC(),
        0, 0,
        backgroundTex->GetWidth(),
        backgroundTex->GetHeight(),
        RGB(255, 0, 255)
    );
    SetTextColor(_hdc, RGB(227, 253, 255));
    RECT nameRc = rc;
    nameRc.bottom -= 50;
    GDISelector namefont(_hdc, FontType::CARDTITLE);
    DrawText(_hdc, name.c_str(), -1, &nameRc, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);

    RECT descRc = rc;
    descRc.top += 50;
    GDISelector descfont(_hdc, FontType::CARDDESC);
    DrawText(_hdc, desc.c_str(), -1, &descRc, DT_CENTER | DT_BOTTOM | DT_WORDBREAK);
}

void EnchantCard::OnClick()
{
    targetScale = 0.f;


    GET_SINGLE(CardManager)->DelayClearCards(0.2f);

	Player* player = GET_SINGLE(PlayerManager)->GetPlayer();
    if (player)
    {
        LaserProjectile* laser = GET_SINGLE(SceneManager)->GetCurScene()->Spawn<LaserProjectile>(Layer::PROJECTILE, {0,0},{0,50});
		player->AddProjectile(laser);
	}

}

void EnchantCard::DisappearCard()
{
    targetScale = 0.f;


    destroyDelay = .5f;
    waitingDestroy = true;
}

void EnchantCard::SetInfo(const wchar_t* name, const wchar_t* desc, const wchar_t* fileName)
{
    this->name = name;
    this->desc = desc;
    this->fileName = fileName;
 
    itemTex = GET_SINGLE(ResourceManager)->GetTexture(fileName);
    backgroundTex = GET_SINGLE(ResourceManager)->GetTexture(L"CardBackground1");
}
