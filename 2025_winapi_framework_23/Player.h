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
    void FixedUpdate(float _fixedDT) override;
    void Render(HDC _hdc) override;
    void EnterCollision(Collider* _other) override;
    void StayCollision(Collider* _other) override;
    void ExitCollision(Collider* _other) override;
private:
    void ShootProjectile();
    Vec2 GetShootDir();
public:
    bool CanShoot() const { return fireTimer >= fireCooldown; }
private:
    Texture* m_pTex;
    Texture* m_lineTex;
    Rigidbody* rb;
	float fireCooldown;
	float fireTimer = 0;
	//vector<PlayerProjectile*> projectiles;
};

