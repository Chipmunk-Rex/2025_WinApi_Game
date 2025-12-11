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
#include "HealPlayerCard.h"
#include "PlayerMaxHealthCard.h"

CardDB::CardDB()
{
	cards = {
		{ L"달", L"아무 능력 없는 \n 달이 추가됩니다.", L"Projectile_Moon", new DefaultBallCard(), 3,CardType::Skill,1},
		{ L"지구", L"회수 시 적 충돌횟수만큼 \n 체력을 회복시켜주는 \n지구를 얻습니다(최대3)", L"Projectile_Earth", new SlowBallCard(), 3,  CardType::Skill,2},
		{ L"체력 증가", L"최대 체력이 10%만큼\n증가합니다", L"Card_Health", new PlayerMaxHealthCard(), 5,CardType::Stat,1},
		{ L"속도 증가", L"이동 속도가 20%만큼\n증가합니다." , L"Plane", new MoveSpeedCard(), 5,CardType::Stat,1},
		{ L"회복", L"체력을 전부\n회복합니다.", L"Card_Heal", new HealPlayerCard() , 3,CardType::Stat,10},
		{ L"탄 크기 증가", L"발사체 크기가 \n 15% 증가합니다." , L"Card_BigSize", new ProjectileSizeCard(), 4,CardType::Stat,2},

		{ L"토성", L"고리로 광역 공격을 하는 \n 토성을 획득합니다", L"Projectile_Saturn", new LaserBallCard(), 3, CardType::StrongSkill,3},
		{ L"공속 증가", L"발사 쿨타임이 \n25% 감소합니다." , L"Player_Turret_Outlined", new FireRateCard(), 5,CardType::Stat,4},

		{ L"블랙홀", L"블랙홀로 붕괴하는 \n불안정한 적색거성을 \n 얻습니다.", L"Projectile_Blackhole", new BlackholeCard(), 3, CardType::StrongSkill,8},
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

void CardDB::Reset()
{
	{
		for (auto c : cards)
			c.baseCard->Reset();
	}
}

