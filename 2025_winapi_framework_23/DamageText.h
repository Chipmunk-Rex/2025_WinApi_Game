#pragma once
#include "Object.h"
class DamageText : public Object
{
private:
	DamageText();
public:
	void Update() override;
	// Object을(를) 통해 상속됨'
	void Render(HDC _hdc) override;
};

