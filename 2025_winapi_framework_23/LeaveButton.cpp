#include "pch.h"
#include "LeaveButton.h"
#include "Button.h"
#include "Object.h"
#include "SceneManager.h"
#include "EnemyTestScene.h"

LeaveButton::LeaveButton()
{
    SetPos({ 640, 360 });
    SetSize({ 200, 80 });

    AddComponent<Button>();
}

LeaveButton::~LeaveButton()
{
}

void LeaveButton::Update()
{

}

void LeaveButton::LateUpdate()
{
    Object::LateUpdate();
}


void LeaveButton::Render(HDC hdc)
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
    DrawText(hdc, L"³ª°¡±â", -1, &rc, DT_CENTER | DT_CENTER | DT_SINGLELINE);

    GDISelector pen(hdc, PenType::RED);
    GDISelector brush(hdc, BrushType::HOLLOW);



    ComponentRender(hdc);
}

void LeaveButton::OnClick()
{
    exit(0);
}
