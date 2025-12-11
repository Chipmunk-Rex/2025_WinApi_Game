#pragma once
#include "Player.h"
#include "Health.h"
class UIManager
{
	DECLARE_SINGLE(UIManager);
public:
	bool isHovering();
	void SetHovering(bool isHover);
private:
	bool isHover;
};

