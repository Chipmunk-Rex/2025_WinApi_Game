#include "pch.h"
#include "PlayerInfoUI.h"
#include "ResourceManager.h"
#include "PlayerManager.h"
#include "Texture.h"
#include "PlayerProjectile.h"

PlayerInfoUI::PlayerInfoUI()
{
    score = 0;
    timeSec = 0.f;
    level = 1;

    curExp = 0.f;
    maxExp = 1.f;
    curHealth = 0.f;
    maxHealth = 1.f;
}

PlayerInfoUI::~PlayerInfoUI()
{
}

void PlayerInfoUI::Update()
{
    auto player = GET_SINGLE(PlayerManager)->GetPlayer();
    float delta = fDT * 20.f;

    SetLevel(player->GetLevel());
    SetScore(GET_SINGLE(PlayerManager)->GetScore());

    curExp += (player->GetExp() - curExp) * delta;
    maxExp = player->GetExpToLevel();

    curHealth += (GET_SINGLE(PlayerManager)->GetPlayerHealth() - curHealth) * delta;
    maxHealth = GET_SINGLE(PlayerManager)->GetPlayerMaxHealth();

    timeSec += fDT;
}

void PlayerInfoUI::Render(HDC hdc)
{
    DrawSideBarriors(hdc);
    DrawTime(hdc);
    DrawLevel(hdc);
    DrawScore(hdc);
    DrawProjectileIcons(hdc);
    DrawExpBar(hdc);
    DrawHpBar(hdc);
}

void PlayerInfoUI::DrawSideBarriors(HDC hdc)
{
    Texture* leftTex = GET_SINGLE(ResourceManager)->GetTexture(L"BarrierL");
    TransparentBlt(hdc, 891, 0, 385, 800,
        leftTex->GetTextureDC(), 0, 0,
        leftTex->GetWidth(), leftTex->GetHeight(), RGB(255, 0, 255));

    Texture* rightTex = GET_SINGLE(ResourceManager)->GetTexture(L"BarrierR");
    TransparentBlt(hdc, 0, 0, 385, 700,
        rightTex->GetTextureDC(), 0, 0,
        rightTex->GetWidth(), rightTex->GetHeight(), RGB(255, 0, 255));
}

void PlayerInfoUI::DrawTime(HDC hdc)
{
    int minutes = (int)(timeSec / 60);
    int seconds = (int)(timeSec) % 60;

    std::wstring txt = L"TIME " + std::to_wstring(minutes) + L":" +
        (seconds < 10 ? L"0" : L"") + std::to_wstring(seconds);

    RECT rc{ 10, 20, 220, 60 };

    SetTextColor(hdc, RGB(227, 253, 255));
    GDISelector font(hdc, FontType::CARDTITLE);
    DrawText(hdc, txt.c_str(), -1, &rc, DT_LEFT | DT_SINGLELINE);
}

void PlayerInfoUI::DrawLevel(HDC hdc)
{
    int y = WINDOW_HEIGHT - 185 - 50;

    std::wstring txt = L"LVL " + std::to_wstring(level);

    RECT rc{ 15, y, 215, y + 40 };
    GDISelector font(hdc, FontType::CARDTITLE);
    DrawText(hdc, txt.c_str(), -1, &rc, DT_LEFT | DT_SINGLELINE);
}

void PlayerInfoUI::DrawScore(HDC hdc)
{
    int right = WINDOW_WIDTH - 20;

    std::wstring txt = L"SCORE " + std::to_wstring(score);

    RECT rc{ right - 330, 20, right - 30, 60 };
    GDISelector font(hdc, FontType::CARDTITLE);
    DrawText(hdc, txt.c_str(), -1, &rc, DT_RIGHT | DT_SINGLELINE);
}

void PlayerInfoUI::DrawProjectileIcons(HDC hdc)
{
    int right = WINDOW_WIDTH - 40;
    int topY = 20;

    float width = 100;
    int left = right - 210;

    int iconW = 64;
    int iconH = 64;

    int iconX = left + width / 2 - iconW / 2;
    int firstIconY = topY + 135 + 20;

    int gap12 = 80;
    int gapNormal = 65;

    const auto& projQueue = GET_SINGLE(PlayerManager)->GetPlayerProjectiles();
    std::queue<PlayerProjectile*> temp = projQueue;

    int maxShow = 6;
    int index = 0;

    while (!temp.empty() && index < maxShow)
    {
        PlayerProjectile* proj = temp.front();
        temp.pop();

        const Texture* tex = proj->GetIconTexture();
        if (tex)
        {
            int drawY = 0;

            if (index == 0)
                drawY = firstIconY;
            else if (index == 1)
                drawY = firstIconY + gap12;
            else
                drawY = firstIconY + gap12 + (index - 1) * gapNormal;

            TransparentBlt(
                hdc,
                iconX,
                drawY,
                iconW,
                iconH,
                tex->GetTextureDC(),
                0, 0,
                tex->GetWidth(),
                tex->GetHeight(),
                RGB(255, 0, 255)
            );
        }

        index++;
    }
}

void PlayerInfoUI::DrawExpBar(HDC hdc)
{
    int leftX = 0;
    int lvlY = WINDOW_HEIGHT - 185;

    int barW = 250;
    int barH = 24;
    int barX = leftX + 15;

    int barY = lvlY + 40;
    float ratio = maxExp > 0 ? curExp / maxExp : 0.f;
    if (ratio > 1.f) ratio = 1.f;

    RECT textRc{ barX, barY - 40, barX + 200, barY };

    SetTextColor(hdc, RGB(255, 255, 255));
    GDISelector font(hdc, FontType::CARDTITLE);

    std::wstring txt = std::to_wstring((int)curExp) + L" / " + std::to_wstring((int)maxExp);
    DrawText(hdc, txt.c_str(), -1, &textRc, DT_LEFT | DT_SINGLELINE);

    RECT outline{ barX, barY, barX + barW, barY + barH };
    Rectangle(hdc, outline.left, outline.top, outline.right, outline.bottom);

    RECT fill{
        barX + 1,
        barY + 1,
        barX + (int)(ratio * barW) - 1,
        barY + barH - 1
    };

    HBRUSH brush = CreateSolidBrush(RGB(90, 197, 232));
    FillRect(hdc, &fill, brush);
    DeleteObject(brush);
}

void PlayerInfoUI::DrawHpBar(HDC hdc)
{
    int leftX = 0;
    int lvlY = WINDOW_HEIGHT - 185;

    int barW = 250;
    int barH = 24;
    int barX = leftX + 15;

    int expY = lvlY + 40;
    int barY = expY + barH + 40;

    float ratio = maxHealth > 0 ? curHealth / maxHealth : 0.f;
    if (ratio > 1.f) ratio = 1.f;

    int hp = GET_SINGLE(PlayerManager)->GetPlayerHealth();
    std::wstring txt = std::to_wstring(hp) + L" / " + std::to_wstring((int)maxHealth);

    RECT textRc{ barX, barY - 40, barX + 200, barY };
    SetTextColor(hdc, RGB(255, 60, 60));
    GDISelector font(hdc, FontType::CARDTITLE);
    DrawText(hdc, txt.c_str(), -1, &textRc, DT_LEFT | DT_SINGLELINE);

    RECT outline{ barX, barY, barX + barW, barY + barH };
    Rectangle(hdc, outline.left, outline.top, outline.right, outline.bottom);

    RECT fill{
        barX + 1,
        barY + 1,
        barX + (int)(ratio * barW) - 1,
        barY + barH - 1
    };

    HBRUSH brush = CreateSolidBrush(RGB(255, 87, 98));
    FillRect(hdc, &fill, brush);
    DeleteObject(brush);
}

void PlayerInfoUI::SetScore(int s)
{
    score = s;
}

void PlayerInfoUI::SetTime(float sec)
{
    timeSec = sec;
}

void PlayerInfoUI::SetLevel(int lvl)
{
    level = lvl;
}

