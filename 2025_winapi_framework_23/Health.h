#pragma once
#include "Component.h"
class Health : public Component
{
public:
	Health();
	~Health();
public:
	void Init() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;
public:
	void SetHealth(double value);
	void TakeDamage(double damage);
	bool GetIsDead();
private:
	double m_health;
	double m_maxHealth;
	bool m_isDead;

};

