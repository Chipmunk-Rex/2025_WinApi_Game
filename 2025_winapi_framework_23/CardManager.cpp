#include "pch.h"
#include "CardManager.h"
#include "CardUI.h"
#include "CardDB.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

void CardManager::AddCard(CardUI* card)
{
    m_cards.push_back(card);
}

void CardManager::ClearCards()
{
    for (auto c : m_cards)
        c->SetDead();
    m_cards.clear();
}

void CardManager::DelayClearCards(float delay)
{   
    clearDelay = delay;
    waitingClear = true;
}

void CardManager::ClearAllCards()
{
    for (auto c : m_cards)
        c->DisappearCard();
}

void CardManager::Update()
{
    if (waitingClear)
    {
        clearDelay -= fDT;
        if (clearDelay <= 0.f)
        {
            waitingClear = false;
            ClearCards();
        }
    }
}

void CardManager::SpawnCards(int count)
{
    ClearCards();
    //SET_TIME_SCALE(0);
    Vec2 size = { 200, 300 };
    float spacing = 250;
    float cx = WINDOW_WIDTH / 2;
    float cy = WINDOW_HEIGHT / 2;
    GET_SINGLE(ResourceManager)->Play(L"SFX_CardAppearSound");

    vector<CardInfo> infos = CardDB::GetRandomCard(count);

    auto scene = GET_SINGLE(SceneManager)->GetCurScene();
    if (!scene)
        return;

    size_t n = infos.size();
    if (n == 0)
        return; 

    float startX = cx - spacing * (static_cast<float>(n - 1) * 0.5f);

    for (size_t i = 0; i < n; ++i)
    {
        const CardInfo& info = infos[i];

        Vec2 pos = { startX + spacing * static_cast<float>(i), cy };
        CardUI* card = scene->Spawn<CardUI>(Layer::UI, pos, size);
        card->SetInfo(info);
        AddCard(card);
    }
}
