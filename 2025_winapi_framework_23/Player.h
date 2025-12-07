#pragma once
#include "Object.h"
#include "PlayerProjectile.h"
//class PlayerProjectile;
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
    bool CanShoot() const { return fireTimer >= fireCooldown && projectiles.size() != 0;}
    void AddProjectile(PlayerProjectile* _proj) { projectiles.push(_proj); _proj->SetActive(false); }

    // Level/Exp
    int GetLevel() const { return level; }
    int GetExp() const { return exp; }
    int GetExpToLevel() const { return expToLevel; }
    void AddExp(int amount)
    {
        exp += amount;
        while (exp >= expToLevel)
        {
            exp -= expToLevel;
            LevelUp();
        }
    }

private:
    void LevelUp();

private:
    Texture* leftTexture;
    Texture* middleTexture;
    Texture* rightTexture;
    Texture* m_turretTex;
    Texture* m_turretMaskTex;
private:
	Texture* currentTexture;
    Rigidbody* rb;
	float fireCooldown;
	float fireTimer = 0;
	std::queue<PlayerProjectile*> projectiles;

    // Progression
    int level = 1;
    int exp = 0;
    int expToLevel = 100;
};

