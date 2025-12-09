#pragma once
#include <string>

class BaseCard;
enum CardType
{
    Stat, Skill, StrongSkill
};

struct CardInfo
{
    std::wstring name;
    std::wstring desc;
    std::wstring fileName;
    BaseCard* baseCard = nullptr;
    int maxCount = 1;
    CardType cardType;
};
