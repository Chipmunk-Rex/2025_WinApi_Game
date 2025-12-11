#pragma once
#include "BaseCard.h"
#include "Health.h"
class HealPlayerCard : public BaseCard
{
	void OnApply(Player& player) override
	{
		Health* health = player.GetComponent<Health>();
		health->SetHealth(health->GetMaxHealth());
	}
};