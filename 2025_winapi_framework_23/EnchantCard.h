#pragma once
#include "Object.h"
#include <string>
class EnchantCard : public Object
{
public:
    EnchantCard();
    ~EnchantCard();
public:
    void Update() override;
    // Object을(를) 통해 상속됨
    void Render(HDC _hdc) override;
public:
    void EnterCollision(Collider* _other) override;
    void StayCollision(Collider* _other) override;
    void ExitCollision(Collider* _other) override;
    void SetInfo(const wchar_t* name, const wchar_t* desc);
private:
    std::wstring name;
    std::wstring desc;

    bool isHovered;
    float hoverScale;

};

