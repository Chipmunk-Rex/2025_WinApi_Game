#include "pch.h"
#include "PlayerInfoUI.h"
#include "ResourceManager.h"

PlayerInfoUI::PlayerInfoUI()
{
    score = 0;
    timeSec = 60.0f;
    level = 1;
}

PlayerInfoUI::~PlayerInfoUI()
{
}

void PlayerInfoUI::Update()
{
}

void PlayerInfoUI::Render(HDC hdc)
{
    int right = WINDOW_WIDTH - 40;
    int bottom = WINDOW_HEIGHT - 40;

    int leftX = 20;
    int topY = 20;
    int lvlY = WINDOW_HEIGHT - 120;

    {
        int minutes = (int)(timeSec / 60);
        int seconds = (int)(timeSec) % 60;

        wchar_t buf[32];
        swprintf(buf, 32, L"TIME %02d:%02d", minutes, seconds);

        RECT rc;
        rc.left = leftX;
        rc.top = topY;
        rc.right = rc.left + 200;
        rc.bottom = rc.top + 40;

        SetTextColor(hdc, RGB(227, 253, 255));
        GDISelector font(hdc, FontType::CARDTITLE);
        DrawText(hdc, buf, -1, &rc, DT_LEFT | DT_TOP | DT_SINGLELINE);
    }

    {
        std::wstring txt = L"LVL " + std::to_wstring(level);

        RECT rc;
        rc.left = leftX + 15;
        rc.top = lvlY;
        rc.right = rc.left + 200;
        rc.bottom = rc.top + 40;

        SetTextColor(hdc, RGB(227, 253, 255));
        GDISelector font(hdc, FontType::CARDTITLE);
        DrawText(hdc, txt.c_str(), -1, &rc, DT_LEFT | DT_TOP | DT_SINGLELINE);
    }

    int barWidth = 40;
    int barHeight = 100;
    int barGap = 15;

    int baseX = right - (barWidth * 3 + barGap * 2);
    int baseY = bottom - barHeight;

    {
        GDISelector pen(hdc, PenType::GREEN);
        GDISelector brush(hdc, BrushType::HOLLOW);

        for (int i = 0; i < 3; i++)
        {
            int x = baseX + i * (barWidth + barGap);

            RECT rc;
            rc.left = x;
            rc.top = baseY;
            rc.right = x + barWidth;
            rc.bottom = baseY + barHeight;

            Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
        }
    }

    {
        std::wstring scoreText = L"SCORE " + std::to_wstring(1000);

        RECT rc;
        rc.left = baseX - 150;
        rc.top = topY;
        rc.right = rc.left + 300;
        rc.bottom = rc.top + 40;

        SetTextColor(hdc, RGB(227, 253, 255));
        GDISelector font(hdc, FontType::CARDTITLE);
        DrawText(hdc, scoreText.c_str(), -1, &rc, DT_RIGHT | DT_TOP | DT_SINGLELINE);
    }
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
