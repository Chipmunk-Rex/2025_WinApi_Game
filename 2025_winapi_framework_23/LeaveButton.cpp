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
    Vec2 p = GetPos();
    Vec2 s = GetSize();

    GDISelector pen(hdc, PenType::RED);
    GDISelector brush(hdc, BrushType::HOLLOW);

    RECT_RENDER(hdc, p.x, p.y, s.x, s.y);


    ComponentRender(hdc);
}

void LeaveButton::OnClick()
{
    exit(0);
}
