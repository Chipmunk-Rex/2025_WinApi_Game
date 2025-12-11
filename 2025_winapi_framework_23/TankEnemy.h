#pragma once
#include "Enemy.h"
#include "CloseRangeEnemy.h"
class TankEnemy : public CloseRangeEnemy
{
public:
    TankEnemy();
public:
    void Update() override;
    // Object을(를) 통해 상속됨'
    void Render(HDC _hdc) override;
    void HandleHitEvent(double _prev, double _health) override;
};

