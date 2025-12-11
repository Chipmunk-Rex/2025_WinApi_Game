#include "pch.h"
#include "Health.h"
#include "Enemy.h"
#include "SceneManager.h"

Health::Health() : m_health(0), m_maxHealth(0), m_isDead(false), m_destroyOnDead(true)
{
}

Health::~Health()
{
}

void Health::Init()
{
	m_maxHealth = m_health;
}

void Health::LateUpdate()
{
}

void Health::Render(HDC _hdc)
{

}

void Health::SetHealth(double value)
{
	m_maxHealth = m_health = value;
}

void Health::SetCurrentHealth(double value)
{
	m_health = value;
}

void Health::SetMaxHealth(double value)
{
	m_maxHealth = value;
}

void Health::TakeDamage(double damage)
{
	if (m_isDead)
		return;
	double prev = m_health;
	m_health -= damage;
	RaiseEvent(prev);
	if (m_health <= 0)
	{
		m_isDead = true;
		if (m_destroyOnDead)
			GET_SINGLE(SceneManager)->RequestDestroy(GetOwner());
	}
}

void Health::RaiseEvent(double _prevHealth)
{
	if (m_isDead) return;
	for (auto a : functions)
	{
		a(_prevHealth, m_health);
	}
}

bool Health::GetIsDead()
{
	return m_isDead;
}

void Health::AddListener(std::function<void(double, double)> delegate)
{
	functions.push_back(delegate);
}
