#include "pch.h"
#include "Background.h"
#include "ResourceManager.h"
#include "Texture.h"

Background::Background()
    : tex(nullptr)
{
    tex = GET_SINGLE(ResourceManager)->GetTexture(L"Background_Space");
}

Background::~Background()
{
}

void Background::Update()
{
    // advance scroll offset
    offsetY += scrollSpeed * fDT;
    // wrap to avoid overflow
    LONG height = tex ? tex->GetHeight() : 0;
    if (height > 0)
    {
        while (offsetY >= height) offsetY -= (float)height;
        while (offsetY < 0) offsetY += (float)height;
    }
}

void Background::Render(HDC _hdc)
{
    if (!tex) return;
    Vec2 pos = GetPos();
    Vec2 size = GetSize();

    LONG srcW = tex->GetWidth();
    LONG srcH = tex->GetHeight();

    int destX = (int)(pos.x - size.x / 2);
    int destY = (int)(pos.y - size.y / 2);
    int destW = (int)size.x;
    int destH = (int)size.y;

    // Scale factor between source texture and destination rectangle
    float scaleH = (srcH > 0) ? ((float)destH / (float)srcH) : 1.0f;

    // Convert source offset to destination pixels
    int destOffsetY = (int)(offsetY * scaleH) % destH;

    // Draw two full stretched copies, offset to create a seamless vertical scroll
    // First copy (shifted up by destOffsetY)
    TransparentBlt(
        _hdc,
        destX,
        destY - destOffsetY,
        destW,
        destH,
        tex->GetTextureDC(),
        0,
        0,
        srcW,
        srcH,
        RGB(255, 0, 255));

    // Second copy (wrap-around after the first)
    TransparentBlt(
        _hdc,
        destX,
        destY - destOffsetY + destH,
        destW,
        destH,
        tex->GetTextureDC(),
        0,
        0,
        srcW,
        srcH,
        RGB(255, 0, 255));
}
