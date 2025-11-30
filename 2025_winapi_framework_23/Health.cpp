#include "pch.h"
#include "Health.h"
#include "Enemy.h"
#include "SceneManager.h"

Health::Health() : m_health(0) , m_maxHealth(0), m_isDead(false)
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
	if (m_isDead)
		GET_SINGLE(SceneManager)->RequestDestroy(GetOwner());
}

void Health::Render(HDC _hdc)
{
	
}

void Health::SetHealth(double value)
{
	m_maxHealth = m_health = value;
}

void Health::TakeDamage(double damage)
{
	m_health -= damage;
	RaiseEvent();
	if (m_health <= 0)
	{
		m_isDead = true;
	}
}

void Health::RaiseEvent()
{
	for (auto a : functions)
	{
		a(m_health);
	}
}

bool Health::GetIsDead()
{
	return m_isDead;
}

void Health::AddListener(std::function<void(int)> delegate)
{
	functions.push_back(delegate);
}
