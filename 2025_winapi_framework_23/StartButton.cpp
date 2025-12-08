#include "pch.h"
#include "StartButton.h"
#include "Button.h"
#include "Object.h"
#include "SceneManager.h"
#include "EnemyTestScene.h"

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
    Vec2 p = GetPos();
    Vec2 s = GetSize();

    GDISelector pen(hdc, PenType::RED);
    GDISelector brush(hdc, BrushType::HOLLOW);

    RECT_RENDER(hdc, p.x, p.y, s.x, s.y);


    ComponentRender(hdc);
}

void StartButton::OnClick()
{
    GET_SINGLE(SceneManager)->LoadScene(L"EnemyTestScene");
}
