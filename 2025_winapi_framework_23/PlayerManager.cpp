#include "pch.h"
#include "PlayerManager.h"

void PlayerManager::AddExp(int amount)
{
    if (!_player || amount <= 0) return;
    _player->AddExp(amount);
	score += amount;
}
