#pragma once
#include "Object.h"

class LeaveButton : public Object
{
public:
    LeaveButton();
    virtual ~LeaveButton();

    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC _hdc) override;
    virtual void OnClick() override;
};
