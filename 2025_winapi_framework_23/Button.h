#pragma once
#include "Component.h"
#include "Vec2.h"

class Button : public Component
{
public:
    Button();
    virtual ~Button();

    virtual void Init() override;
    virtual void LateUpdate() override;

    virtual void OnHoverEnter();
    virtual void OnHoverExit();
    virtual void OnClick();

private:
    bool isHovered;
    bool wasHovered;

    Vec2 pos;
    Vec2 size;
};
