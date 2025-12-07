#pragma once
#include <vector>

class CardUI;

class CardManager
{
    DECLARE_SINGLE(CardManager);

public:
    void AddCard(CardUI* card);
    void ClearCards();
    void DelayClearCards(float delay);
    void ClearAllCards();
    void Update();
    void SpawnCards(int count);

private:
private:
    std::vector<CardUI*> m_cards;

    float clearDelay = 0.f;
    bool waitingClear = false;
};
