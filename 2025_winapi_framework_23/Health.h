#pragma once
#include <functional>
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
	void AddListener(std::function<void(int)> delegate);
	void RaiseEvent();
	double GetMaxHealth() { return m_maxHealth; }
private:
	double m_health;
	double m_maxHealth;
	bool m_isDead;
	std::vector<std::function<void(int)>> functions;
};

