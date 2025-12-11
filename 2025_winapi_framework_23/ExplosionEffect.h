#pragma once
#include "Object.h"
class ExplosionEffect : public Object
{
public:
	ExplosionEffect();
	virtual ~ExplosionEffect();
public:
	void Update() override;
	void Render(HDC _hdc) override;
private:
	float _timer = 0;
};

