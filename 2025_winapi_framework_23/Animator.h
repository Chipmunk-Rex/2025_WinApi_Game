#pragma once
#include "Component.h"
class Texture;
class Animation;
class Animator : public Component
{
public:
    Animator();
    ~Animator();

public:
    void Init() override;
    void LateUpdate() override;
    void Render(HDC _hdc) override;

public:
    void CreateAnimation(const wstring& _name, Texture* _tex,
        Vec2 _lt, Vec2 _sliceSize, Vec2 _step,
        UINT _frameCount, float _durationPerFrame);

    Animation* FindAnimation(const wstring& _name);

    void Play(const wstring& _name, PlayMode _mode = PlayMode::Loop,
        int _loopCount = 1, float _speed = 1.0f);

    void Stop();
    void Pause();
    void Resume();

    // Explicitly set destination render size for current animation
    void SetCurrentRenderSize(Vec2 size);

public:
    Animation* GetCurrent() const { return m_curAnimation; }
    bool IsPaused() const { return m_paused; }

private:
    std::unordered_map<std::wstring, Animation*> m_mapAnim;
    Animation* m_curAnimation;
    bool       m_paused;
};
