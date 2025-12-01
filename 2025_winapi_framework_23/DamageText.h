#pragma once
#include "Object.h"
class DamageText : public Object
{
public:
	DamageText();
public:
	void Update() override;
	// Object을(를) 통해 상속됨'
	void Render(HDC _hdc) override;
	void SetDamage(double damage) { text = damage; }
public:
	double text;
private:
	double timer;
	double lifeTime;
};

