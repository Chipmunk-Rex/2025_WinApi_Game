#include "pch.h"
#include "MouseObject.h"
#include "InputManager.h"
#include "Collider.h"
#include "Vec2.h"

MouseObject::MouseObject()
{
    AddComponent<Collider>()->SetSize({1,1});
}

MouseObject::~MouseObject()
{
   
}

void MouseObject::Update()
{
    Vec2 mousePos = GET_SINGLE(InputManager)->GetMousePos();
    SetPos(mousePos);

}

void MouseObject::Render(HDC _hdc)
{
}

