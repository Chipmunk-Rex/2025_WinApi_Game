#pragma once
#include "BaseCard.h"
#include "Player.h"

class FireRateCard : public BaseCard
{
protected:
    void OnApply(Player& player) override
    {
        player.GetFireCooldownStat().GetMultiplierRef() *= 0.75;
    }
};
