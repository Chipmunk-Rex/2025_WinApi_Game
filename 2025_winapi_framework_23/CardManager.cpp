#include "pch.h"
#include "CardManager.h"
#include "EnchantCard.h"

void CardManager::RequestSpawnCards(int count)
{
    spawnRequest.count = count;
}

void CardManager::AddCard(EnchantCard* card)
{
    m_cards.push_back(card);
}

void CardManager::ClearCards()
{
    for (auto c : m_cards)
        c->SetDead();
    m_cards.clear();
}

void CardManager::ClearAllCards()
{
    for (auto c : m_cards)
        c->DisappearCard();
}
