#include "pch.h"
#include "CardDB.h"

#include <cstdlib>

const std::vector<CardInfo> CardDB::cards =
{
    { L"공 증가", L"발사되는 공 개수가 하나 증가합니다" },
    { L"체력 증가", L"최대 체력이 10% 증가합니다" },
    { L"속도 증가", L"이동 속도가 20% 증가합니다." },
    { L"회복", L"체력을 전부 회복합니다." }
};

const std::vector<CardInfo> CardDB::GetRandomCard(int count)
{
  
    std::vector<CardInfo> vec;
    for (int i = 0; i < count; i++)
    {
        int idx = rand() % cards.size();
        vec.push_back(cards[idx]);
    }

    return vec;
}
