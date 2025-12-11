#include "pch.h"
#include "PlayerInfoUI.h"
#include "ResourceManager.h"
#include "PlayerManager.h"
#include "Texture.h"
#include "PlayerProjectile.h"


PlayerInfoUI::PlayerInfoUI()
{
    score = 0;
    timeSec = 0.0f;
    level = 1;

    curExp = 0.f;
    maxExp = 0.f;
    curHealth = 0.f;
    maxHealth = 0.f;
}


PlayerInfoUI::~PlayerInfoUI()
{
}

void PlayerInfoUI::Update()
{
	auto player = GET_SINGLE(PlayerManager)->GetPlayer();

	SetLevel(player->GetLevel());
	SetScore(GET_SINGLE(PlayerManager)->GetScore());
    float deltaTime = fDT * 20;
    
	curExp += (player->GetExp() - curExp) * deltaTime;
	maxExp = player->GetExpToLevel();

    curHealth += (GET_SINGLE(PlayerManager)->GetPlayerHealth() - curHealth) * deltaTime ;
	maxHealth = GET_SINGLE(PlayerManager)->GetPlayerMaxHealth();

	timeSec += fDT;
}


void PlayerInfoUI::Render(HDC hdc)
{
    int right = WINDOW_WIDTH - 40;
    int bottom = WINDOW_HEIGHT - 40;

    int leftX = 5;
    int topY = 20;
    int lvlY = WINDOW_HEIGHT - 185;

    int minutes = (int)(timeSec / 60);
    int seconds = (int)(timeSec) % 60;
    // 타임텍스트 -----------------------------
    std::wstring timeText = L"TIME "
        + std::to_wstring(minutes)
        + L":"
        + (seconds < 10 ? L"0" : L"")
        + std::to_wstring(seconds);

    RECT timeRc;
    timeRc.left = leftX + 10;
    timeRc.top = topY;
    timeRc.right = timeRc.left + 220;
    timeRc.bottom = timeRc.top + 40;

    SetTextColor(hdc, RGB(227, 253, 255));
    GDISelector font1(hdc, FontType::CARDTITLE);
    DrawText(hdc, timeText.c_str(), -1, &timeRc, DT_LEFT | DT_TOP | DT_SINGLELINE);

    // 레벨텍스트 -----------------------------
    std::wstring lvlTxt = L"LVL " + std::to_wstring(level);

    RECT lvlRc;
    lvlRc.left = leftX + 15;
    lvlRc.top = lvlY - 50;
    lvlRc.right = lvlRc.left + 200;
    lvlRc.bottom = lvlRc.top + 40;

    DrawText(hdc, lvlTxt.c_str(), -1, &lvlRc, DT_LEFT | DT_TOP | DT_SINGLELINE);
    // 점수텍스트 -----------------------------
    std::wstring scoreText = L"SCORE " + std::to_wstring(score);

    RECT scoreRc;
    scoreRc.left = right - 330;
    scoreRc.top = topY;
    scoreRc.right = scoreRc.left + 300;
    scoreRc.bottom = scoreRc.top + 40;

    DrawText(hdc, scoreText.c_str(), -1, &scoreRc, DT_RIGHT | DT_TOP | DT_SINGLELINE);
    RECT skillOutline;

    float projectileContainerWidth = 100;
    skillOutline.left = right - 150;
    skillOutline.top = topY + 100;
    skillOutline.right = skillOutline.left + projectileContainerWidth;
    skillOutline.bottom = skillOutline.top + 350;

    Rectangle(hdc, skillOutline.left, skillOutline.top, skillOutline.right, skillOutline.bottom);

        // projectial 큐 (탄창) ----------
        const auto& projQueue = GET_SINGLE(PlayerManager)->GetPlayerProjectiles();

        int maxShow = 6;
        int index = 0;

        int iconW = 64;
        int iconH = 64;
        int iconX = skillOutline.left + projectileContainerWidth / 2 - iconW / 2;
        int iconY = skillOutline.top + 20;
        int margin = 65;

        std::queue<PlayerProjectile*> temp = projQueue;

        while (!temp.empty() && index < maxShow)
        {
            PlayerProjectile* proj = temp.front();
            temp.pop();

            const Texture* tex = proj->GetIconTexture();
            if (tex != nullptr)
            {
                TransparentBlt(
                    hdc,
                    iconX,
                    iconY + index * margin,
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



    int barWidth = 250;
    int barHeight = 24;

    int barX = leftX + 15;

    // 여기부터 경험치임 -----------------------------
    int expBarY = lvlY + 40;
    float expRatio = maxExp > 0 ? curExp / maxExp : 0.f;
    if (expRatio > 1.f) expRatio = 1.f;

    RECT expTextRc;
    expTextRc.left = barX;
    expTextRc.top = expBarY - 40;
    expTextRc.right = expTextRc.left + 200;
    expTextRc.bottom = expTextRc.top + 40;

    SetTextColor(hdc, RGB(255, 255, 255));

    GDISelector font2(hdc, FontType::CARDTITLE);
    GDISelector brush(hdc, BrushType::WHITE);

    std::wstring expText = std::to_wstring((int)curExp) + L" / " + std::to_wstring((int)maxExp);
    DrawText(hdc, expText.c_str(), -1, &expTextRc, DT_LEFT | DT_TOP | DT_SINGLELINE);

    RECT expOutline;
    expOutline.left = barX;
    expOutline.top = expBarY;
    expOutline.right = barX + barWidth;
    expOutline.bottom = expBarY + barHeight;

    GDISelector brush2(hdc, BrushType::WHITE);

    Rectangle(hdc, expOutline.left, expOutline.top, expOutline.right, expOutline.bottom);

    RECT expFill;
    expFill.left = barX + 1;
    expFill.top = expBarY + 1;
    expFill.right = barX + (int)(expRatio * barWidth) - 1;
    expFill.bottom = expBarY + barHeight - 1;


    HBRUSH whiteBrush = CreateSolidBrush(RGB(90, 197, 232));
    FillRect(hdc, &expFill, whiteBrush);
    DeleteObject(whiteBrush);
    // 여기부터 체력임 -----------------------------
    int hpBarY = expBarY + barHeight + 40;
    float hpRatio = maxHealth > 0 ? curHealth / maxHealth : 0.f;
    if (hpRatio > 1.f) hpRatio = 1.f;

    RECT hpTextRc;
    hpTextRc.left = barX;
    hpTextRc.top = hpBarY - 40;
    hpTextRc.right = hpTextRc.left + 200;
    hpTextRc.bottom = hpTextRc.top + 40;

    int realHp = GET_SINGLE(PlayerManager)->GetPlayerHealth();
    std::wstring hpText = std::to_wstring(realHp) + L" / " + std::to_wstring((int)maxHealth);

    SetTextColor(hdc, RGB(255, 60, 60));
    DrawText(hdc, hpText.c_str(), -1, &hpTextRc, DT_LEFT | DT_TOP | DT_SINGLELINE);

    RECT hpOutline;
    hpOutline.left = barX;
    hpOutline.top = hpBarY;
    hpOutline.right = barX + barWidth;
    hpOutline.bottom = hpBarY + barHeight;

    Rectangle(hdc, hpOutline.left, hpOutline.top, hpOutline.right, hpOutline.bottom);

    RECT hpFill;
    hpFill.left = barX + 1;
    hpFill.top = hpBarY + 1;
    hpFill.right = barX + (int)(hpRatio * barWidth) - 1;
    hpFill.bottom = hpBarY + barHeight - 1;
    
    HBRUSH redBrush = CreateSolidBrush(RGB(255, 87, 98));
    FillRect(hdc, &hpFill, redBrush);
    DeleteObject(redBrush);
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
