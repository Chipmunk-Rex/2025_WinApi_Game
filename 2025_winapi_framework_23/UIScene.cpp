#include "pch.h"
#include "UIScene.h"
#include "EnchantCard.h"
void UIScene::Init()
{
	cout << "a";
	Object* obj = new EnchantCard;

	Spawn<EnchantCard>(Layer::DEFAULT, { WINDOW_WIDTH / 2, 0 },{100,100});
}

void UIScene::Update()
{
	Scene::Update();
    
}

void UIScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);


}
