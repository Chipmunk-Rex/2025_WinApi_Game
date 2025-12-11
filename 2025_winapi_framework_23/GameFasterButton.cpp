#include "pch.h"
#include "GameFasterButton.h"
#include "Button.h"
#include "Object.h"
#include "SceneManager.h"
#include "EnemyTestScene.h"

GameFasterButton::GameFasterButton()
{

    AddComponent<Button>();
}

GameFasterButton::~GameFasterButton()
{
}

void GameFasterButton::Update()
{

}

void GameFasterButton::LateUpdate()
{
    Object::LateUpdate();
}


void GameFasterButton::Render(HDC hdc)
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
    DrawText(hdc, speedText.c_str(), -1, &rc, DT_CENTER | DT_CENTER | DT_SINGLELINE);

    GDISelector pen(hdc, PenType::RED);
    GDISelector brush(hdc, BrushType::HOLLOW);



    ComponentRender(hdc);
}

void GameFasterButton::OnClick()
{
    SET_TIME_SCALE(speed);
}

void GameFasterButton::SetSpeed(std::wstring speedText, int speed)
{
    this->speedText = speedText + L"X";
    this->speed = speed;
}
