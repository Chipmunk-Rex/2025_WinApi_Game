#include "pch.h"
#include "EnchantCard.h"
#include "Collider.h"
#include "SceneManager.h"
EnchantCard::EnchantCard()
{
	
}

EnchantCard::~EnchantCard()
{
}

void EnchantCard::Update()
{

}

void EnchantCard::Render(HDC _hdc)
{
    Vec2 pos = GetPos();
    Vec2 size = GetSize();

    RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);

   

    RECT rc;
    rc.left = (LONG)(pos.x - size.x / 2);
    rc.top = (LONG)(pos.y - size.y / 2);
    rc.right = (LONG)(pos.x + size.x / 2);
    rc.bottom = (LONG)(pos.y + size.y / 2);

    GDISelector font(_hdc, FontType::TITLE);

    DrawText(
        _hdc,
        name.c_str(),
        -1,
        &rc,
        DT_CENTER | DT_VCENTER | DT_SINGLELINE
    );

    rc.left = (LONG)(pos.x - size.x / 2);
    rc.top = (LONG)(pos.y - size.y / 2);
    rc.right = (LONG)(pos.x + size.x / 2);
    rc.bottom = (LONG)(pos.y + size.y / 2) + 50;

    DrawText(
        _hdc,
        desc.c_str(),
        -1,
        &rc,
        DT_CENTER | DT_VCENTER | DT_SINGLELINE
    );

    PenType penColor = PenType::GREEN;
  
    GDISelector pen(_hdc, penColor);
    GDISelector brush(_hdc, BrushType::HOLLOW);
    RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);

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

void EnchantCard::SetInfo(const wchar_t* name, const wchar_t* desc)
{
    this->name = name;
    this->desc = desc;
}









