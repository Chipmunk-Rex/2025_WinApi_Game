#include "pch.h"
#include "CardManager.h"
#include "CardUI.h"
#include "CardDB.h"
#include "SceneManager.h"
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
    Vec2 size = { 200, 300 };
    float spacing = 250;
    float cx = WINDOW_WIDTH / 2;
    float cy = WINDOW_HEIGHT / 2;

    vector<CardInfo> infos = CardDB::GetRandomCard(count);

    auto SpawnOne = [&](Vec2 pos, CardInfo& info)
    {
        // Use current scene to spawn UI
        auto scene = GET_SINGLE(SceneManager)->GetCurScene();
        if (!scene)
            return;
        CardUI* card = scene->Spawn<CardUI>(Layer::UI, pos, size);
        card->SetInfo(info);
        AddCard(card);
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
