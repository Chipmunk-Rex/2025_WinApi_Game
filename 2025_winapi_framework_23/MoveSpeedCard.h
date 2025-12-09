#pragma once
#include "BaseCard.h"
class MoveSpeedCard : public BaseCard
{
protected:
    void OnApply(Player& player) override
    {
		player.SetMoveSpeed(player.GetMoveSpeed() + 0.20f);
    }
};
