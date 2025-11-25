#pragma once
#include "Object.h"

class MouseObject : public Object
{
public:
    MouseObject();
    ~MouseObject();
public:
    void Update() override;
    // Object을(를) 통해 상속됨
    void Render(HDC _hdc) override;
};
