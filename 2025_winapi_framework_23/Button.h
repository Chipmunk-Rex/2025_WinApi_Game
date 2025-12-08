#pragma once
#include "Component.h"
#include "Vec2.h"

class Button : public Component
{
public:
    Button();
    virtual ~Button();
    
    virtual void OnHoverEnter();
    virtual void OnHoverExit();
    virtual void OnClick();
    // Component을(를) 통해 상속됨
    void Init() override;
    void LateUpdate() override;
    void Render(HDC _hdc) override;

private:
    bool isHovered;
    bool wasHovered;

    Vec2 pos;
    Vec2 size;
};
