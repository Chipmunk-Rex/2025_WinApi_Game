#pragma once
#include "Object.h"
class Texture;
class Rigidbody;
class Player :
    public Object
{
public:
    Player();
    virtual ~Player();
public:
    void Update() override;

    // Object을(를) 통해 상속됨
    void Render(HDC _hdc) override;
    void EnterCollision(Collider* _other) override;
    void StayCollision(Collider* _other) override;
    void ExitCollision(Collider* _other) override;
private:
    void CreateProjectile();
    Vec2 GetShootDir();
private:
    Texture* m_pTex;
    Texture* m_lineTex;
    Rigidbody* rb;
};

