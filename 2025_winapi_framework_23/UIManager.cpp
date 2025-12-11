#include "pch.h"
#include "UIManager.h"

bool UIManager::isHovering()
{
	return isHover;
}

void UIManager::SetHovering(bool isHover)
{
	this->isHover = isHover;
}
