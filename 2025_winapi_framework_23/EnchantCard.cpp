#include "pch.h"
#include "EnchantCard.h"
#include "Collider.h"
#include "SceneManager.h"
EnchantCard::EnchantCard()
{
	AddComponent<Collider>();
}

EnchantCard::~EnchantCard()
{
}

void EnchantCard::Update()
{

}

void EnchantCard::Render(HDC _hdc)
{
	//HBRUSH hbrush = ::CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	//HBRUSH holdbrush = (HBRUSH)::SelectObject(_hdc, hbrush);
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	RECT_RENDER(_hdc, pos.x, pos.y
		, size.x, size.y);
	//::SelectObject(_hdc, holdbrush);
	//::DeleteObject(hbrush);

	::TextOut(_hdc, 0, 0, L"증강 등장", 2);
	GDISelector font(_hdc, FontType::TITLE);
	::TextOut(_hdc, 10, 10, L"", 2);
	PenType penColor = PenType::GREEN;


	ComponentRender(_hdc);
}

void EnchantCard::EnterCollision(Collider* _other)
{
	cout << "EnterCollision" << endl;

	if (_other->GetName() == L"PlayerBullet")
	{
		
	}

	

}

void EnchantCard::StayCollision(Collider* _other)
{
	cout << "StayCollision" << endl;
}

void EnchantCard::ExitCollision(Collider* _other)
{
	cout << "ExitCollision" << endl;
}








