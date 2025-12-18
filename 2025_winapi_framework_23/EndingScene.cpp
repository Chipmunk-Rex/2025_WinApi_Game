#include "pch.h"
#include "EndingScene.h"
#include "Object.h"
#include "SceneManager.h"
#include "Button.h";
#include "StartButton.h"
#include "LeaveButton.h"
#include "Background.h"
#include "ResourceManager.h"


void EndingScene::Init()
{
    SET_TIME_SCALE(1);

    GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
    GET_SINGLE(ResourceManager)->Play(L"BGM_Ending");

    Spawn<Background>(Layer::BACKGROUND, { WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2 }, { WINDOW_WIDTH, WINDOW_HEIGHT })->SetTexture(L"StartScene_Space");
    Spawn<LeaveButton>(Layer::UI, { 1100, 300 }, { 200, 80 });
    Spawn<StartButton>(Layer::UI, { 1100, 250 }, { 200, 80 })->SetText(L"다시하기");

    creditLines = {
      L"적대적인 다른 우주의 침공이 시작되었을 때,",
      L"그들은 행성을 들고 우리 우주를 던져 부수려 했다.",

      L"하지만 아무도 예상하지 못했다.",
      L"당신이 ‘행성의 주권자’로 각성할 줄은.",

      L"전투기에 몸을 실은 당신은",
      L"무너져가던 우주의 마지막 희망이었다.",
      L"그리고 당신은 해냈다.",

      L"당신이 제어한 행성들은",
      L"적들의 궤도를 산산히 부수었고,",
      L"침공은 완전히 멈추었다.",

      L"이 우주는 지켜졌다.",
      L"그것도 당신의 손으로, 확실하게.",

      L"오늘, 우주의 주인은 당신이었다",
       L"축하합니다! -신희섭, 고민수, 윤완희-"
    };

}



void EndingScene::Update()
{
    creditTime += fDT * 0.5;
}
void EndingScene::Render(HDC _hdc)
{
    Scene::Render(_hdc);

    float startY = WINDOW_HEIGHT + 700;    
    float endY = -4150.f;                 
    float t = min(1.0f, creditTime / 15.f);  

    float curY = startY + (endY - startY) * t; 

    int spacing = 350; 
    int centerX = WINDOW_WIDTH / 2;

    GDISelector font(_hdc, FontType::CARDTITLE);
    SetTextColor(_hdc, RGB(227, 253, 255));

    for (int i = 0; i < creditLines.size(); i++)
    {
        RECT rc;
        rc.left = centerX - 400;
        rc.top = curY + i * spacing;
        rc.right = rc.left + 800;
        rc.bottom = rc.top + 40;

        int alpha = (int)(255 * t);
        alpha = max(0, min(255, alpha));

        DrawText(_hdc, creditLines[i].c_str(), -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
}
