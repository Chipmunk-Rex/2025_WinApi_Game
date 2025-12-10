#include "pch.h"
#include <vector>

#include "CardInfo.h"

class CardDB
{
public:
    virtual ~CardDB() ;
public:
    static const std::vector<CardInfo> cards;
    static const std::vector<CardInfo> GetRandomCard(int count);
};
