#pragma once
#include "Player.h"
class BaseCard
{
public:
    virtual ~BaseCard() {}

    bool CanAcquire(int maxCount) const { return appliedCount < maxCount; }
    void Apply(Player& player) { OnApply(player); ++appliedCount; }
    void Remove(Player& player) { OnRemove(player); if (appliedCount > 0) --appliedCount; }
    int GetAppliedCount() const { return appliedCount; }

protected:
    virtual void OnApply(Player& player) = 0;
    virtual void OnRemove(Player& player) {}

private:
    int appliedCount = 0;
};

