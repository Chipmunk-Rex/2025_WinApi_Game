#include "pch.h"
#include "DamageText.h"
#include "SceneManager.h"
#include <sstream>

DamageText::DamageText() : text(0), lifeTime(1.2f), timer(0)
{

}

void DamageText::Update()
{
	timer += fDT;
	if (timer >= lifeTime)
		GET_SINGLE(SceneManager)->RequestDestroy(this);

	Translate({ fDT * 5.f, fDT * -10.f, });
}

void DamageText::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	
	GDISelector pen = GDISelector(_hdc, PenType::CARDTEXT);

	std::string str = std::format("{:.0f}", text);
	
	const wstring wstr = std::to_wstring(std::stod(str));

	TextOut(_hdc, pos.x, pos.y, wstr.c_str(), str.length());



	SetBkMode(_hdc, TRANSPARENT);
}
