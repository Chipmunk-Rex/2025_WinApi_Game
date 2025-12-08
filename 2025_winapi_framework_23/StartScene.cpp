#include "pch.h"
#include "StartScene.h"
#include "Object.h"
#include "SceneManager.h"
#include "Button.h";
#include "StartButton.h"
#include "LeaveButton.h"


void StartScene::Init()
{
    Spawn<StartButton>(Layer::UI, { 640, 360 }, { 200, 80 });
    Spawn<LeaveButton>(Layer::UI, { 640, 0 }, { 200, 80 });
    cout << "¹öÆ° »ý¼ºµÊ" << endl;
}



void StartScene::Update()
{
}

void StartScene::Render(HDC _hdc)
{
    Scene::Render(_hdc);
}
