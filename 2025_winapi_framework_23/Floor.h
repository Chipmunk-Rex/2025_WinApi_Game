#pragma once
#include "Object.h"
class Floor :
    public Object
{
public:
    Floor();
    ~Floor();    
public:
    void Update() override;
    void Render(HDC _hdc) override;
public:
    void SetSize(Vec2 _size) override;
private:
	Collider* collider;
};

