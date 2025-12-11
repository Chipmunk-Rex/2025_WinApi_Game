#include "pch.h"
#include "Button.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "UIManager.h"
#include "Object.h"

Button::Button()
    : isHovered(false), wasHovered(false)
{
}

Button::~Button()
{
}

void Button::Init()
{
    pos = GetOwner()->GetPos();
    size = GetOwner()->GetSize();
}

void Button::LateUpdate()
{
   
    pos = GetOwner()->GetPos();
    size = GetOwner()->GetSize();

    Vec2 mouse = GET_SINGLE(InputManager)->GetMousePos();

    bool inside =
        mouse.x >= pos.x - size.x * 0.5f &&
        mouse.x <= pos.x + size.x * 0.5f &&
        mouse.y >= pos.y - size.y * 0.5f &&
        mouse.y <= pos.y + size.y * 0.5f;

    if (inside && !wasHovered)
    {
        isHovered = true;
        GET_SINGLE(ResourceManager)->Play(L"SFX_HoverSound");
        OnHoverEnter();
    }

    if (!inside && wasHovered)
    {
        isHovered = false;
        OnHoverExit();
    }

    if (inside && GET_SINGLE(InputManager)->IsDown(KEY_TYPE::LBUTTON))
    {
        OnClick();               
        GetOwner()->OnClick();   
    }


    wasHovered = inside;
}

void Button::Render(HDC _hdc)
{
 

}

void Button::OnHoverEnter() {
    GET_SINGLE(UIManager)->SetHovering(true);
    GET_SINGLE(ResourceManager)->Play(L"SFX_HoverSound");
}
void Button::OnHoverExit() {
    GET_SINGLE(UIManager)->SetHovering(false);

}
void Button::OnClick() {}
