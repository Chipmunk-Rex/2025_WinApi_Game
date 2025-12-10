#pragma once
#include "Scene.h"

class EndingScene : public Scene
{
public:
	// Scene을(를) 통해 상속됨
	void Init() override;
	void Update() override;
	void Render(HDC _hdc) override;

private:
	float creditTime = 0.f;
	vector<wstring> creditLines;
	bool isEnd;


};
