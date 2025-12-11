#pragma once
class StatValue
{
public:
	StatValue(float _baseValue = 0.f, float _multiplier = 1.f)
		: BaseValue(_baseValue), Multiplier(_multiplier)
	{
	}
	float GetValue() const { return BaseValue * Multiplier; }
	void SetMultiplier(float _mult) { Multiplier = _mult; }
	void AddMultiplier(float _mult) { Multiplier += _mult; }
	float& GetMultiplierRef() { return Multiplier; }
private:
	float BaseValue;
	float Multiplier;
public:
	float operator=(float _value)
	{
		BaseValue = _value;
		return BaseValue;
	}
};