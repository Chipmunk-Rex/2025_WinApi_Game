#pragma once
#include "Object.h"

class PlayerInfoUI : public Object
{
public:
    PlayerInfoUI();
    ~PlayerInfoUI();

public:
    void Update() override;
    void Render(HDC hdc) override;

    void SetScore(int s);
    void SetTime(float sec);
    void SetLevel(int lvl);

private:
    int score;
    float timeSec;
    int level;
    float curExp = 0.f;
    float maxExp = 1.f;
    float curHealth = 0.f;
    float maxHealth = 1.f;


};
