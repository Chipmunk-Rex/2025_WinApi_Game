#pragma once
#include "Player.h"
class PlayerManager
{
	DECLARE_SINGLE(PlayerManager);
public:
	void SetPlayer(Player* _player) { this->_player = _player; }
	Player* GetPlayer() const { return _player; }

	void AddExp(int amount);
	int GetScore() const 
	{
		return score;
	}
private:
	Player* _player;
	int score = 0;
};

