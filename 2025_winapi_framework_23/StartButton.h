#pragma once
#include "Object.h"

class StartButton : public Object
{
public:
    StartButton();
    virtual ~StartButton();

    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC _hdc) override;
    virtual void OnClick() override;
};
