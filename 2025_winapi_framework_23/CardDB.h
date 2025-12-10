#include "pch.h"
#include <vector>
#include "Defines.h"
#include "CardInfo.h"

class CardDB
{
    DECLARE_SINGLE_CD(CardDB);

public:
    static const std::vector<CardInfo> GetRandomCard(int count);
	static const std::vector<CardInfo>& GetAllCards() { return GetInst()->cards; }
private:
    std::vector<CardInfo> cards;
};
