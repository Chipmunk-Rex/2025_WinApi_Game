#pragma once
#include "Enemy.h"
class CloseRangeEnemy : public Enemy
{
public:
    CloseRangeEnemy();
    ~CloseRangeEnemy();
public:
    void Update() override;
    // Object을(를) 통해 상속됨'
    void Render(HDC _hdc) override;
    void HandleChangeHealth(int _health) override;
};

