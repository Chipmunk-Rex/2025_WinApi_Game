#include "pch.h"
#include "StartButton.h"
#include "Button.h"
#include "Object.h"
#include "SceneManager.h"
#include "EnemyTestScene.h"
#include "ResourceManager.h"

StartButton::StartButton()
{
    SetPos({ 640, 360 });
    SetSize({ 200, 80 });

    AddComponent<Button>();
}

StartButton::~StartButton()
{
}

void StartButton::Update()
{
    
}

void StartButton::LateUpdate()
{
    Object::LateUpdate();
}


void StartButton::Render(HDC hdc)
{
    Vec2 pos = GetPos();
    Vec2 scaled = GetSize();

    SetTextColor(hdc, RGB(227, 253, 255));
    RECT rc;
    rc.left = (LONG)(pos.x - scaled.x * 0.5f);
    rc.top = (LONG)(pos.y - scaled.y * 0.5f);
    rc.right = (LONG)(pos.x + scaled.x * 0.5f);
    rc.bottom = (LONG)(pos.y + scaled.y * 0.5f);
   
    GDISelector namefont(hdc, FontType::CARDTITLE);
    DrawText(hdc, text.c_str(), -1, &rc, DT_CENTER | DT_CENTER | DT_SINGLELINE);

    GDISelector pen(hdc, PenType::RED);
    GDISelector brush(hdc, BrushType::HOLLOW);
    ComponentRender(hdc);
}

void StartButton::OnClick()
{
    GET_SINGLE(ResourceManager)->Play(L"SFX_Start");

    GET_SINGLE(SceneManager)->LoadScene(L"EnemyTestScene");
}

void StartButton::SetText(std::wstring getText)
{
    text = getText;
}

