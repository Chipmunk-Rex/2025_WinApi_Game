#pragma once
#include "CloseRangeEnemy.h"
class DownAttackEnemy : public CloseRangeEnemy
{
public:
    DownAttackEnemy();
public:
    void Update() override;
    // Object을(를) 통해 상속됨'
    void Render(HDC _hdc) override;
    void HandleHitEvent(double _prev, double _health) override;
public:
    bool m_isAttacking;
    bool m_isDead;
};

