#include "pch.h"
#include "StartScene.h"
#include "Object.h"
#include "SceneManager.h"
#include "Button.h";
#include "StartButton.h"
#include "LeaveButton.h"
#include "Background.h"
#include "ResourceManager.h"
    

void StartScene::Init()
{
    Spawn<Background>(Layer::BACKGROUND, { WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2 }, { WINDOW_WIDTH, WINDOW_HEIGHT })->SetTexture(L"StartScene_Space");
    Spawn<StartButton>(Layer::UI, { 640, 360 }, { 200, 80 })->SetText(L"시작하기");
    Spawn<LeaveButton>(Layer::UI, { 640, 440 }, { 200, 80 });
    cout << "버튼 생성됨" << endl;

    GET_SINGLE(ResourceManager)->Play(L"BGM");
}



void StartScene::Update()
{
}

void StartScene::Render(HDC _hdc)
{
    Scene::Render(_hdc);

    RECT rc;
    rc.left = 315;
    rc.top = 380;
    rc.right = rc.left + 650;
    rc.bottom = rc.top - 250;
    GDISelector namefont(_hdc, FontType::CARDTITLE);
    SetTextColor(_hdc, RGB(227, 253, 255));
    DrawText(_hdc, L"PLANET DEFENDER", -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
