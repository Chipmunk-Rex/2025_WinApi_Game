#include "pch.h"
#include "TankEnemy.h"
#include "Collider.h"

TankEnemy::TankEnemy()
{
	auto* col = GetComponent<Collider>();
	col->SetSize({ 100,50 });
}
void TankEnemy::Update()
{
	CloseRangeEnemy::Update();
}
void TankEnemy::Render(HDC _hdc)
{
	CloseRangeEnemy::Render(_hdc);
}

void TankEnemy::HandleHitEvent(double _prev, double _health)
{
	CloseRangeEnemy::HandleHitEvent(_prev,_health);
}
