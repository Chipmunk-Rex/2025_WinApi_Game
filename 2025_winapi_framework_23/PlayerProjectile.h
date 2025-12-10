#pragma once
#include "Projectile.h"
class PlayerProjectile : public Projectile
{
public:
    PlayerProjectile();
    ~PlayerProjectile() override;
public:
    void Update() override;
    void Render(HDC _hdc) override;
    void EnterCollision(Collider* _other) override;
    void StayCollision(Collider* _other) override;
    void ExitCollision(Collider* _other) override;
public:
    
    void Scale(Vec2 _s) override
    {
        this->SetSize(defaultSize * _s);
    }
public:
    void Shoot(Vec2 _dir) override;
    void SetDamage(int damage) { _damage = damage; }
    bool CanCollect() const { return canCollect; }
public:
    virtual const Texture* GetIconTexture() { return this->GetTexture(); }
protected:
	void SetDefaultSize(Vec2 _size) { defaultSize = _size; }
private:
    int _damage;
	bool canCollect = false;
    Vec2 defaultSize;
};

