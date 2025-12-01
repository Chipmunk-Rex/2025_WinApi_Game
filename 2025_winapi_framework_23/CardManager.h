#pragma once
#include <vector>
#include "Vec2.h"
#include "EnchantCard.h"

struct CardSpawnRequest
{
    int count;
};

class CardManager
{
    DECLARE_SINGLE(CardManager);

public:
    void RequestSpawnCards(int count);

    bool HasSpawnRequest() const { return spawnRequest.count > 0; }
    CardSpawnRequest GetSpawnRequest() const { return spawnRequest; }
    void ClearSpawnRequest() { spawnRequest.count = 0; }

    void AddCard(EnchantCard* card);
    void ClearCards();
    void ClearAllCards();

private:
    std::vector<EnchantCard*> m_cards;
    CardSpawnRequest spawnRequest = { 0 };
};
