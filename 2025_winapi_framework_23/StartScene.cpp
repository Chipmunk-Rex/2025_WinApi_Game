#include "pch.h"
#include "StartScene.h"
#include "Object.h"
#include "SceneManager.h"
#include "Button.h";
#include "StartButton.h"
#include "LeaveButton.h"
#include "Background.h"
    

void StartScene::Init()
{
    Spawn<Background>(Layer::BACKGROUND, { WINDOW_WIDTH / 2 , WINDOW_HEIGHT / 2 }, { WINDOW_WIDTH, WINDOW_HEIGHT })->SetTexture(L"StartScene_Space");
    Spawn<StartButton>(Layer::UI, { 640, 360 }, { 200, 80 });
    Spawn<LeaveButton>(Layer::UI, { 640, 440 }, { 200, 80 });
    cout << "¹öÆ° »ý¼ºµÊ" << endl;
}



void StartScene::Update()
{
}

void StartScene::Render(HDC _hdc)
{
    Scene::Render(_hdc);
}
