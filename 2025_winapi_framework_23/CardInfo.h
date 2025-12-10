#pragma once
#include <string>

class BaseCard;
enum CardType
{
    Stat, Skill, StrongSkill
};

struct CardInfo
{
    wstring name;
    wstring desc;
    wstring fileName;
    BaseCard* baseCard = nullptr;
    int maxCount = 1;
    CardType cardType;
};
