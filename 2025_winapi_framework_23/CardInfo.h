#pragma once
#include <string>

class BaseCard;

struct CardInfo
{
    std::wstring name;
    std::wstring desc;
    std::wstring fileName;
    BaseCard* baseCard = nullptr;
    int maxCount = 1;
};
