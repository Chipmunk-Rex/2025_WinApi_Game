#pragma once
#include "Object.h"
#include <string>
#include <memory>
#include "Texture.h"
#include "CardInfo.h"
#include "BaseCard.h"

class CardUI : public Object
{
public:
    CardUI();
    ~CardUI();

public:
    void Update() override;
    void Render(HDC _hdc) override;

    void OnClick();
    void DisappearCard();
    void SetInfo(const CardInfo& info);

private:
    std::wstring name;
    std::wstring desc;
    std::wstring fileName;
    std::shared_ptr<BaseCard> baseCard = nullptr;
    int maxCount = 1;

    bool isHovered;
    bool wasHovered;

    float hoverScale;
    float targetScale;

    float destroyDelay;
    bool waitingDestroy;

    Texture* backgroundTex;
    Texture* itemTex;
};
