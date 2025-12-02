#pragma once
#include "Player.h"
class PlayerManager
{
	DECLARE_SINGLE(PlayerManager);
public:
	void SetPlayer(Player* _player) { this->_player = _player; }
	Player* GetPlayer() const { return _player; }
private:
	Player* _player;
};

