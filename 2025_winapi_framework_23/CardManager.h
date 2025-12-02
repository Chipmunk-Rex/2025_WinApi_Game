#pragma once
#include <vector>

class EnchantCard;

class CardManager
{
    DECLARE_SINGLE(CardManager);

public:
    void AddCard(EnchantCard* card);
    void ClearCards();
    void DelayClearCards(float delay);
    void ClearAllCards();

    void RequestSpawnCards(int count);
    bool HasSpawnRequest() const { return spawnRequest.count > 0; }
    void ClearSpawnRequest() { spawnRequest.count = 0; }
    auto GetSpawnRequest() const { return spawnRequest; }

    void Update();

private:
    struct CardSpawnRequest
    {
        int count = 0;
    };

private:
    std::vector<EnchantCard*> m_cards;
    CardSpawnRequest spawnRequest;

    float clearDelay = 0.f;
    bool waitingClear = false;
};
