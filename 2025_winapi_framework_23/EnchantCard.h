#pragma once
#include "Object.h"
#include <string>
#include "Texture.h"

class EnchantCard : public Object
{
public:
    EnchantCard();
    ~EnchantCard();

public:
    void Update() override;
    void Render(HDC _hdc) override;

    void OnClick();
    void DisappearCard();
    void SetInfo(const wchar_t* name, const wchar_t* desc, const wchar_t* fileName);

private:
    std::wstring name;
    std::wstring desc;
    std::wstring fileName;

    bool isHovered;
    bool wasHovered;

    float hoverScale;
    float targetScale;

    float destroyDelay;
    bool waitingDestroy;

    Texture* itemTex;
};
