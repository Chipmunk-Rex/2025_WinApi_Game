#include "pch.h"
#include "CardDB.h"

#include <cstdlib>
#include <algorithm>
#include "LaserBallCard.h"
#include "MoveSpeedCard.h"
#include "SlowBallCard.h"
#include "DefaultBallCard.h"
#include "BaseCard.h"
#include "FireRateCard.h"
#include "BlackholeCard.h"
#include "ProjectileSizeCard.h"
#include "PlayerManager.h"


CardDB::CardDB()
{
    cards = {
        { L"달", L"아무 능력 없는 달이 추가됩니다.", L"Projectile_Moon", new DefaultBallCard(), 3,CardType::Skill,1},
        { L"지구", L"피격 시 적이 느려지는 특징이 있는 지구를 획득합니다.", L"Projectile_Earth", new SlowBallCard(), 3,  CardType::Skill,2},
        { L"체력 증가", L"최대 체력이 10%만큼\n증가합니다", L"Plane", nullptr, 1,CardType::Stat,1},
        { L"속도 증가", L"이동 속도가 20%만큼\n증가합니다." , L"Plane", new MoveSpeedCard(), 5,CardType::Stat,1},
        { L"회복", L"체력을 전부 회복합니다.", L"Plane", nullptr, 1,CardType::Stat,3},
        { L"탄 크기 증가", L"발사체 크기가 20% 증가합니다." , L"Plane", new ProjectileSizeCard(), 5,CardType::Stat,2},

        { L"토성", L"고리로 광역 공격을 하는 토성을 추가합니다.", L"Projectile_Saturn", new LaserBallCard(), 3, CardType::StrongSkill,3},
        { L"공속 증가", L"발사 쿨타임이 10% 감소합니다." , L"Player_Turret_Outlined", new FireRateCard(), 5,CardType::Stat,4},

        { L"블랙홀", L"블랙홀로 붕괴하는 \n불안정한 적색거성을 \n 얻습니다.", L"Projectile_Blackhole", new BlackholeCard(), 3, CardType::StrongSkill,5},
    };
}

CardDB::~CardDB()
{
    for (auto& info : cards)
    {
        if (info.baseCard)
        {
            delete info.baseCard;
            info.baseCard = nullptr;
        }
    }
}

const std::vector<CardInfo> CardDB::GetRandomCard(int count)
{
    CardDB* db = CardDB::GetInst();
    auto player = GET_SINGLE(PlayerManager)->GetPlayer();
    int playerLevel = player->GetLevel();

    std::vector<CardInfo> huboCard;
    huboCard.reserve(db->cards.size());

    for (const auto& info : db->cards)
    {
 
        if (playerLevel < info.afterlevel)
            continue;

        if (info.baseCard == nullptr)
        {
            huboCard.push_back(info);
        }
        else if (info.baseCard->CanAcquire(info.maxCount))
        {
            huboCard.push_back(info);
        }
    }

    std::vector<CardInfo> selected;
    if (huboCard.empty() || count <= 0)
        return selected;

 
    count = min(count, (int)huboCard.size());

    for (int i = 0; i < count; ++i)
    {
        int randIndex = rand() % huboCard.size();
        selected.push_back(huboCard[randIndex]);

        huboCard.erase(huboCard.begin() + randIndex);
    }

    return selected;
}

