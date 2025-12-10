#include "pch.h"
#include "PlayerManager.h"

void PlayerManager::AddExp(int amount)
{
    if (!_player || amount <= 0) return;
    _player->AddExp(amount);
	score += amount;
}

double PlayerManager::GetPlayerHealth() const
{
	return _playerHealth->GetCurrentHealth();
}
double PlayerManager::GetPlayerMaxHealth() const
{
	return _playerHealth->GetMaxHealth();
}
