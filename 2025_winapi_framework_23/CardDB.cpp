#include "pch.h"
#include "CardDB.h"

#include <cstdlib>
#include <algorithm>
#include "LaserBallCard.h"
#include "MoveSpeedCard.h"
#include "SlowBallCard.h"
#include "DefaultBallCard.h"
#include "BaseCard.h"

const std::vector<CardInfo> CardDB::cards =
{
    { L"토성 추가", L"고리로 가로 광역 공격을 하는 토성을 추가합니다.", L"Projectile_Saturn", new LaserBallCard(), 3},
    { L"지구 추가", L"피격 시 적이 느려지는 특징이 있는 지구를 추가합니다.", L"Projectile_Earth", new SlowBallCard(), 3},
    { L"달 추가", L"아무 능력 없는 달이 추가됩니다.", L"Projectile_Moon", new DefaultBallCard(), 3},
    //{ L"공 증가", L"발사되는 공 개수가\n하나 증가합니다", L"Plane", new LaserBallCard(), 1 },
    { L"체력 증가", L"최대 체력이 10%만큼\n증가합니다", L"Plane", nullptr, 1},
    { L"속도 증가", L"이동 속도가 20%만큼\n증가합니다." , L"Plane", new MoveSpeedCard(), 5},
    { L"회복", L"체력을 전부 회복합니다.", L"Plane", nullptr, 1 },  
   
};

const std::vector<CardInfo> CardDB::GetRandomCard(int count)
{
    // Build eligible list based on maxCount and current appliedCount
    std::vector<CardInfo> eligible;
    eligible.reserve(cards.size());
    for (const auto& info : cards)
    {
        if (info.baseCard == nullptr)
        {
            //eligible.push_back(info);
        }
        else if (info.baseCard->CanAcquire(info.maxCount))
        {
            eligible.push_back(info);
        }
    }

    std::vector<CardInfo> result;
    if (eligible.empty() || count <= 0)
        return result; // none available

    // Allow duplicates like before, but only from eligible set
    for (int i = 0; i < min(count, eligible.size()); ++i)
    {
        int idx = rand() % eligible.size();
        result.push_back(eligible[idx]);
    }

    return result;
}
