#pragma once
#include "BaseCard.h"
#include "Health.h"
class  PlayerMaxHealthCard : public BaseCard
{
public:
	void OnApply(Player& player) override
	{
		Health* health = player.GetComponent<Health>();
		double currentMaxHealth = health->GetMaxHealth();
		double increasedHealth = currentMaxHealth * 0.1;
		health->SetMaxHealth(currentMaxHealth + increasedHealth);
		health->SetCurrentHealth(health->GetCurrentHealth() + increasedHealth);
	}
};