#pragma once
#include "Object.h"
#include "ResourceManager.h"

class RingEffect : public Object
{
public:
    RingEffect() : _duration(0.4f), _elapsed(0.f), _maxRadius(200.f), _startRadius(10.f) {}
    virtual ~RingEffect() {}

public:
    void Update() override
    {
        _elapsed += fDT;
        float t = (float)min(1.0, _elapsed / _duration);
        // Ease-out
        float eased = 1.0f - (1.0f - t) * (1.0f - t);
        float r = _startRadius + (_maxRadius - _startRadius) * eased;
        SetSize({ r * 2.f, r * 2.f });
        if (_elapsed >= _duration)
        {
            GET_SINGLE(SceneManager)->RequestDestroy(this);
        }
    }

    void Render(HDC _hdc) override
    {
        Vec2 pos = GetPos();
        Vec2 size = GetSize();
        GDISelector brush(_hdc, BrushType::HOLLOW);
        HPEN pen = ::CreatePen(PS_SOLID, 3, RGB(218, 165, 32));
        HGDIOBJ oldPen = ::SelectObject(_hdc, pen);
        ::Ellipse(_hdc,
            (int)(pos.x - size.x / 2),
            (int)(pos.y - size.y / 2),
            (int)(pos.x + size.x / 2),
            (int)(pos.y + size.y / 2));
        ::SelectObject(_hdc, oldPen);
        ::DeleteObject(pen);
    }

public:
    void SetMaxRadius(float r) { _maxRadius = r; }
    void SetStartRadius(float r) { _startRadius = r; }
    void SetDuration(float d) { _duration = d; }

private:
    float _duration;
    float _elapsed;
    float _maxRadius;
    float _startRadius;
};
