#include "pch.h"
#include "UIScene.h"
#include "EnchantCard.h"
#include "SceneManager.h"
#include "InputManager.h"

void UIScene::Init()
{
}

void UIScene::Update()
{
    Scene::Update();

    if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::A))
        SpawnCards(1);

    if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::B))
        SpawnCards(2);

    if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::C))
        SpawnCards(3);
 
}

void UIScene::ClearCards()
{
   
    auto& objs = GetLayerObjects(Layer::DEFAULT);

    for (auto obj : objs)
    {
        if (dynamic_cast<EnchantCard*>(obj))
            obj->SetDead();
    }
}


void UIScene::SpawnCards(int count)
{
    ClearCards();
    cout << "≥™ø»";
    Vec2 size = { 200, 300 };
    float spacing = 250;   
    float centerX = WINDOW_WIDTH / 2;
    float centerY = WINDOW_HEIGHT / 2;

    if (count == 1)
    {
        EnchantCard *card = Spawn<EnchantCard>(Layer::DEFAULT,
            { centerX, centerY }, size);

        card->SetInfo(L"Ω≈»Òº∑", L"∞ÌπŒΩ¥");
        return;
    }

    if (count == 2)
    {
        Spawn<EnchantCard>(Layer::DEFAULT,
            { centerX - spacing / 2, centerY }, size);

        Spawn<EnchantCard>(Layer::DEFAULT,
            { centerX + spacing / 2, centerY }, size);
        return;
    }

    if (count == 3)
    {
        Spawn<EnchantCard>(Layer::DEFAULT,
            { centerX - spacing, centerY }, size);

        Spawn<EnchantCard>(Layer::DEFAULT,
            { centerX, centerY }, size);

        Spawn<EnchantCard>(Layer::DEFAULT,
            { centerX + spacing, centerY }, size);
        return;
    }
}


void UIScene::Render(HDC _hdc)
{
    Scene::Render(_hdc);
}
