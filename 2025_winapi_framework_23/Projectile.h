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
	void EnterCollision(Collider* _other) override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;
public:
    virtual void Shoot(Vec2 _dir)
    {
        GetRigidbody()->SetVelocity(_dir);
    }
protected:
	void SetTexture(Texture* _tex) { m_pTex = _tex; }
	Rigidbody* GetRigidbody() const { return rigidbody; }
private:
    Texture* m_pTex;
	Rigidbody* rigidbody;
};

