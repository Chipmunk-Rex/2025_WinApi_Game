#pragma once
#include "Object.h"
#include "Texture.h"
#include "Health.h"
class Enemy : public Object
{
public:
	Enemy();
	~Enemy();
public:
	void Update() override;
	// Object을(를) 통해 상속됨'
	void Render(HDC _hdc) override;
public:
	void EnterCollision(Collider* _other) override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;
	void SetTex(Texture* _tex) { m_pTex = _tex; }
	double GetMaxHealth() {
		return m_healthCompo->GetMaxHealth();
	}
	virtual void HandleChangeHealth(int _health) {}
private:
	Texture* m_pTex;
	Health* m_healthCompo;
};

