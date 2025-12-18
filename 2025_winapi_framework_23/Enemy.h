#pragma once
#include "Object.h"
#include "Texture.h"
#include "Health.h"
#include "Rigidbody.h"
#include "Player.h"
class Enemy : public Object
{
public:
	Enemy();
	virtual ~Enemy();
public:
	void Update() override;
	// Object을(를) 통해 상속됨'
	void Render(HDC _hdc) override;
public:
	void SetHealth(float value)
	{
		m_healthCompo->SetHealth(value);
	}
	void EnterCollision(Collider* _other) override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;
	void SetTex(Texture* _tex) { m_pTex = _tex; }
	double GetMaxHealth() {
		return m_healthCompo->GetMaxHealth();
	}
	double GetCurHealth() { return m_healthCompo->GetCurrentHealth(); }
	virtual void HandleHitEvent(double _prev, double _health) {}
	Player* GetTarget() {
		return m_target != nullptr ? m_target
			: nullptr;
	}

	Rigidbody* GetRbCompo() {
		return m_rbCompo
			;
	}

	Collider* GetColliderCompo() {
		return m_colliderCompo;
	}
private:
	Texture* m_pTex;
	Health* m_healthCompo;
	Rigidbody* m_rbCompo;
	Collider* m_colliderCompo;
	Player* m_target;
};

