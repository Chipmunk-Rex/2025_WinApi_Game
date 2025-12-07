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
	void AddListener(std::function<void(double, double)> delegate);
	void RaiseEvent(double _prevHealth);
	double GetMaxHealth() { return m_maxHealth; }
	double GetCurrentHealth() { return m_health; }
private:
	double m_health;
	double m_maxHealth;
	bool m_isDead;
	std::vector<std::function<void(double, double)>> functions;
};

