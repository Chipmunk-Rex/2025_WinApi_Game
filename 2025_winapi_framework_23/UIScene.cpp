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
    Spawn<MouseObject>(Layer::PLAYER, { 0,0 }, { 10,10 });
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::UI);

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
   
    auto& objs = GetLayerObjects(Layer::UI);

    for (auto obj : objs)
    {
        if (dynamic_cast<EnchantCard*>(obj))
            obj->SetDead();
    }
}


void UIScene::SpawnCards(int count)
{
    ClearCards();
    cout << "³ª¿È";
    Vec2 size = { 200, 300 };
    float spacing = 250;   
    float centerX = WINDOW_WIDTH / 2;
    float centerY = WINDOW_HEIGHT / 2;
    vector<CardInfo> vec = CardDB::GetRandomCard(count);
    if (count == 1)
    {


        EnchantCard *card = Spawn<EnchantCard>(Layer::UI,
            { centerX, centerY }, size);

        card->SetInfo(vec[0].name.c_str(), vec[0].desc.c_str());
        return;
    }

    if (count == 2)
    {
    
        EnchantCard* card = Spawn<EnchantCard>(Layer::UI,
            { centerX - spacing / 2, centerY }, size);

        card->SetInfo(vec[0].name.c_str(), vec[0].desc.c_str());

        EnchantCard* card2 = Spawn<EnchantCard>(Layer::UI,
            { centerX + spacing / 2, centerY }, size);
        card2->SetInfo(vec[1].name.c_str(), vec[1].desc.c_str());
        return;
    }

    if (count == 3)
    {
        EnchantCard* card = Spawn<EnchantCard>(Layer::UI,
            { centerX - spacing, centerY }, size);

        card->SetInfo(vec[0].name.c_str(), vec[0].desc.c_str());
        EnchantCard* card2 = Spawn<EnchantCard>(Layer::UI,
            { centerX, centerY }, size);

        card2->SetInfo(vec[1].name.c_str(), vec[1].desc.c_str());

        EnchantCard* card3 = Spawn<EnchantCard>(Layer::UI,
            { centerX + spacing, centerY }, size);
        card3->SetInfo(vec[2].name.c_str(), vec[2].desc.c_str());
        return;
    }
}


void UIScene::Render(HDC _hdc)
{
    Scene::Render(_hdc);
}
