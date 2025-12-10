#pragma once
#include "Object.h"
#include "PlayerProjectile.h"
#include "Stat.h"
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
	bool CanShoot() const { return fireTimer >= fireCooldownStat.GetValue() && projectiles.size() != 0; }
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

	// Stat modifiers
	void AddFireCooldownMultiplier(float delta) { fireCooldownStat.AddMultiplier(delta); }
	void AddProjectileScaleMultiplier(float delta) { projectileScaleStat.AddMultiplier(delta); }

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
	Vec2 m_offset;
private:
	std::queue<PlayerProjectile*> projectiles;
	float fireTimer = 0;
	StatValue fireCooldownStat;
	StatValue projectileScaleStat;
public:
	float GetCurrentCooldown() const { return fireTimer / fireCooldownStat.GetValue(); }
	const std::queue<PlayerProjectile*>& GetProjectiles() const { return projectiles; }
private:
	int level = 1;
	int exp = 0;
	int expToLevel = 100;
public:
	float GetMoveSpeed() const { return moveSpeed; }
	void SetMoveSpeed(float speed) { moveSpeed = speed; }
private:
	float moveSpeed = 1;
};

