#include "pch.h"
#include "Floor.h"
#include "Collider.h"
Floor::Floor()
{
	collider = AddComponent<Collider>();
	collider->SetName(L"Floor");
}

Floor::~Floor()
{
}

void Floor::Update()
{
}

void Floor::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Floor::SetSize(Vec2 _size)
{
	Object::SetSize(_size);
	collider->SetSize(_size);
}
