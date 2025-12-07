#include "pch.h"
#include "StartScene.h"
#include "Object.h"
#include "SceneManager.h"
#include "Button.h"

void StartScene::Init()
{
    Object* btn = Spawn<Object>(Layer::UI, { 640, 360 }, { 200, 80 });
    Button* b = btn->AddComponent<Button>();

    b->OnClick = [this]() {
        GET_SINGLE(SceneManager)->LoadScene(L"GameScene");
        };
}

void StartScene::Update()
{
}

void StartScene::Render(HDC _hdc)
{
}
