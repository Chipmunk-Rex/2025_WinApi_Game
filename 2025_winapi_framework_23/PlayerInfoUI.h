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
    void DrawSideBarriors(HDC hdc);
    void DrawTime(HDC hdc);
    void DrawLevel(HDC hdc);
    void DrawScore(HDC hdc);
    void DrawProjectileIcons(HDC hdc);
    void DrawExpBar(HDC hdc);
    void DrawHpBar(HDC hdc);

private:
    int score;
    float timeSec;
    int level;

    float curExp;
    float maxExp;
    float curHealth;
    float maxHealth;
};
