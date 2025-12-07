#pragma once
#include "Player.h"
class BaseCard
{
public:
    virtual ~BaseCard() {}
    virtual void Apply(Player& player) = 0;
    virtual void Remove(Player& player) {}
};

