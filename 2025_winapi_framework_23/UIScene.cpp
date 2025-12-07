#include "pch.h"
#include "CardDB.h"
#include "UIScene.h"
#include "EnchantCard.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "MouseObject.h"
#include "CollisionManager.h"


void UIScene::Init()
{
    cardMgr = (GET_SINGLE(CardManager));
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


void UIScene::SpawnCards(int count)
{
    GET_SINGLE(CardManager)->ClearCards(); 
    Vec2 size = { 200, 300 };
    float spacing = 250;
    float cx = WINDOW_WIDTH / 2;
    float cy = WINDOW_HEIGHT / 2;
        
    vector<CardInfo> infos = CardDB::GetRandomCard(count);

    auto SpawnOne = [&](Vec2 pos, CardInfo& info)
        {
            EnchantCard* card = Spawn<EnchantCard>(Layer::UI, pos, size);
            card->SetInfo(info.name.c_str(), info.desc.c_str(), info.fileName.c_str());
            GET_SINGLE(CardManager)->AddCard(card);
        };

    if (count == 1)
    {
        SpawnOne({ cx, cy }, infos[0]);
        return;
    }
    if (count == 2)
    {
        SpawnOne({ cx - spacing / 2, cy }, infos[0]);
        SpawnOne({ cx + spacing / 2, cy }, infos[1]);
        return;
    }
    if (count == 3)
    {
        SpawnOne({ cx - spacing, cy }, infos[0]);
        SpawnOne({ cx, cy }, infos[1]);
        SpawnOne({ cx + spacing, cy }, infos[2]);
        return;
    }
}




void UIScene::Render(HDC _hdc)
{
    Scene::Render(_hdc);
}