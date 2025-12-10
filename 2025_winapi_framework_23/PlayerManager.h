#pragma once
#include "Player.h"
#include "Health.h"
class PlayerManager
{
	DECLARE_SINGLE(PlayerManager);
public:
	void SetPlayer(Player* _player) { 
		this->_player = _player;
		if (_player != nullptr)
			this->_playerHealth = _player->GetComponent<Health>();
		else
			this->_playerHealth = nullptr;
	}
	Player* GetPlayer() const { return _player; }

	void AddExp(int amount);
	int GetScore() const 
	{
		return score;
	}
	int GetPlayerLevel() const
	{
		if (!_player) return 0;
		return _player->GetLevel();
	}

	double GetPlayerHealth() const;
	double GetPlayerMaxHealth() const;

	const std::queue<PlayerProjectile*>& GetPlayerProjectiles();
private:
	Player* _player;
	Health* _playerHealth;
	int score = 0;
};

