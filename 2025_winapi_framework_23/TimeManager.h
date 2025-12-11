#pragma once

class TimeManager
{
	DECLARE_SINGLE(TimeManager);
public:
	void Init();
	void Update();
public:
	float GetDT() const { return m_dT * m_multiplier; }
	float GetRDT() const { return m_dT; }
	float GetTimeScale() const {
		return m_multiplier
			;
	}
	void SetMultiplier(float value) { m_multiplier = value; }
private:
	LARGE_INTEGER m_llPrevCnt = {};
	LARGE_INTEGER m_llCurCnt = {};
	LARGE_INTEGER m_llFrequency = {};

	// DT(Delta Time)
	float m_dT = 0.f;

	// FPS(Freme pre second)
	UINT m_fps = 0;

	UINT m_frameCnt = 0;
	float m_frameTime = 0.f;
	float m_multiplier = 0.f;
};

