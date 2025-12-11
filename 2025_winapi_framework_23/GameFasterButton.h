#pragma once
#include "Object.h"

class GameFasterButton : public Object
{
public:
    GameFasterButton();
    virtual ~GameFasterButton();

    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void Render(HDC _hdc) override;
    virtual void OnClick() override;
    void SetSpeed(std::wstring speedText, int speed);

private:
    int speed;
    std::wstring speedText;
};
