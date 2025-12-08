#include "pch.h"
#include "StartScene.h"
#include "Object.h"
#include "SceneManager.h"
#include "Button.h"

void StartScene::Init()
{
    Object* btn = Spawn<Object>(Layer::UI, { 640, 360 }, { 200, 80 });

}

void StartScene::Update()
{
}

void StartScene::Render(HDC _hdc)
{
}
