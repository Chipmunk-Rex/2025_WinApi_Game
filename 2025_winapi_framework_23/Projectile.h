#pragma once
#include "Object.h"
#include "Rigidbody.h"
class Texture;
class Rigidbody;
class Projectile :
    public Object
{
public:
    Projectile();
    ~Projectile();
public:
    void Update() override;
    // Object을(를) 통해 상속됨
    void Render(HDC _hdc) override;
public:
    void SetDir(Vec2 _dir)
    {
        rigidbody->SetVelocity(_dir);
    }
	void EnterCollision(Collider* _other) override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;
private:
    Texture* m_pTex;
	Rigidbody* rigidbody;
};

