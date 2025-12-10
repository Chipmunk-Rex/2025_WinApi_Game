#include "pch.h"
#include "CardDB.h"

#include <cstdlib>
#include <algorithm>
#include <memory>
#include "LaserBallCard.h"
#include "MoveSpeedCard.h"
#include "SlowBallCard.h"
#include "DefaultBallCard.h"
#include "BaseCard.h"
#include "FireRateCard.h"
#include "ProjectileSizeCard.h"

static std::shared_ptr<LaserBallCard> s_laserBallCard = std::make_shared<LaserBallCard>();
static std::shared_ptr<SlowBallCard> s_slowBallCard = std::make_shared<SlowBallCard>();
static std::shared_ptr<DefaultBallCard> s_defaultBallCard = std::make_shared<DefaultBallCard>();
static std::shared_ptr<MoveSpeedCard> s_moveSpeedCard = std::make_shared<MoveSpeedCard>();
static std::shared_ptr<FireRateCard> s_fireRateCard = std::make_shared<FireRateCard>();
static std::shared_ptr<ProjectileSizeCard> s_projectileSizeCard = std::make_shared<ProjectileSizeCard>();

const std::vector<CardInfo> CardDB::cards =
{
    { L"토성 추가", L"고리로 광역 공격을 하는 토성을 추가합니다.", L"Projectile_Saturn", s_laserBallCard, 3, CardType::StrongSkill},
    { L"지구 추가", L"피격 시 적이 느려지는 특징이 있는 지구를 추가합니다.", L"Projectile_Earth", s_slowBallCard, 3,  CardType::Skill},
    { L"달 추가", L"아무 능력 없는 달이 추가됩니다.", L"Projectile_Moon", s_defaultBallCard, 3,CardType::Skill},
    //{ L"공 증가", L"발사되는 공 개수가\n하나 증가합니다", L"Plane", new LaserBallCard(), 1 },
    { L"체력 증가", L"최대 체력이 10%만큼\n증가합니다", L"Plane", nullptr, 1,CardType::Stat},
    { L"속도 증가", L"이동 속도가 20%만큼\n증가합니다." , L"Plane", s_moveSpeedCard, 5,CardType::Stat},
    { L"공속 증가", L"발사 쿨타임이 10% 감소합니다." , L"Player_Turret_Outlined", s_fireRateCard, 5,CardType::Stat},
    { L"탄 크기 증가", L"발사체 크기가 20% 증가합니다." , L"Plane", s_projectileSizeCard, 5,CardType::Stat},
    { L"회복", L"체력을 전부 회복합니다.", L"Plane", nullptr, 1,CardType::Stat },
   
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

    for (int i = 0; i < min(count, static_cast<int>(eligible.size())); ++i)
    {
        int idx = rand() % eligible.size();
        result.push_back(eligible[idx]);
    }

    return result;
}
