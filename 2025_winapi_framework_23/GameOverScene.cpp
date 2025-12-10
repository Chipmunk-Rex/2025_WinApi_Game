#include "pch.h"
#include "GameOverScene.h"
#include "Object.h"
#include "SceneManager.h"
#include "Button.h";
#include "StartButton.h"
#include "LeaveButton.h"
#include "Background.h"


void GameOverScene::Init()
{
    Spawn<Background>(Layer::BACKGROUND, { WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2 }, { WINDOW_WIDTH, WINDOW_HEIGHT })->SetTexture(L"StartScene_Space");
    Spawn<LeaveButton>(Layer::UI, { 640, 440 }, { 200, 80 });
    cout << "버튼 생성됨" << endl;
}



void GameOverScene::Update()
{
}

void GameOverScene::Render(HDC _hdc)
{
    Scene::Render(_hdc);

    RECT rc;
    rc.left = 680 - 350;
    rc.top = 380;
    rc.right = rc.left + 650;
    rc.bottom = rc.top - 80;
    GDISelector namefont(_hdc, FontType::CARDTITLE);
    SetTextColor(_hdc, RGB(227, 253, 255));
    DrawText(_hdc, L"당신은 우주 전쟁에서 패배하였습니다..", -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

