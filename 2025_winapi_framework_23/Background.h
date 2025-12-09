#pragma once
#include "Object.h"
class Texture;
class Background : public Object
{
public:
    Background();
    virtual ~Background();
public:
    void Update() override;
    void Render(HDC _hdc) override;
    void SetTexture(std::wstring fileName);
private:
    Texture* tex;
    float scrollSpeed = 50.0f; // pixels per second
    float offsetY = 0.0f;      // current scroll offset in texture space
};
