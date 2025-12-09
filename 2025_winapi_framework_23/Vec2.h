#pragma once
struct Vec2
{
public:
	//Vec2() {}
	Vec2() = default;
	Vec2(float _x, float _y) : x(_x), y(_y) {}
	Vec2(POINT _pt) : x((float)_pt.x), y((float)_pt.y) {}
	Vec2(int _x, int _y) : x((float)_x), y((float)_y) {}
	Vec2(const Vec2& _other) : x(_other.x), y(_other.y) {}
public:
	Vec2 operator + (const Vec2& _vOther) const
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}
	Vec2 operator - (const Vec2& _vOther) const
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}
	Vec2 operator * (const Vec2& _vOther) const
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}
	Vec2 operator * (float _val) const
	{
		return Vec2(x * _val, y * _val);
	}
	Vec2 operator / (float _val) const
	{
		return Vec2(x / _val, y / _val);
	}
	Vec2 operator / (Vec2 _val) const
	{
		return Vec2(x / _val.x, y / _val.y);
	}
	Vec2 operator -() const
	{
		return Vec2(-x, -y);
	}
	// 보류
	//Vec2 operator / (const Vec2& _vOther)
	//{
	//	assert(!(0.f == _vOther.x || 0.f == _vOther.y));
	//	return Vec2(x / _vOther.x, y / _vOther.y);
	//}
	void operator+=(const Vec2& _other)
	{
		x += _other.x;
		y += _other.y;
	}
	void operator-=(const Vec2& _other)
	{
		x -= _other.x;
		y -= _other.y;
	}
	float LengthSquared()
	{
		return x * x + y * y;
	}
	float Length()
	{
		return ::sqrt(LengthSquared());
	}
	Vec2 Normalize()
	{
		float len = Length();
		if (len < FLT_EPSILON)
			return *this;
		Vec2 normalizedVec = { x / len, y / len };
		return normalizedVec;
	}
	float Dot(const Vec2 &_other) const
	{
		return x * _other.x + y * _other.y;
	}
	float Cross(Vec2 _other)
	{
		return x * _other.y - y * _other.x;
	}
	Vec2 Rotate(float _angle)
	{
		float cosA = cosf(_angle);
		float sinA = sinf(_angle);
		return Vec2(x * cosA - y * sinA, x * sinA + y * cosA);
	}
	Vec2 Abs() 
	{
		float absX = abs(x);
		float absY = abs(y);
		return Vec2(absX, absY);
	}
	explicit operator POINT()
	{
		POINT pt;
		pt.x = static_cast<LONG>(x);
		pt.y = static_cast<LONG>(y);
		return pt;
	}

	float GetAngleRad(const Vec2 a) {
		// 내적
		float dot = a.x * x + a.y * y;

		// 크기(길이)
		float magA = std::sqrt(a.x * a.x + a.y * a.y);
		float magB = std::sqrt(x * x + y * y);

		// 0으로 나누는 것 방지
		if (magA == 0 || magB == 0) return 0.0f;

		float cosTheta = dot / (magA * magB);

		// acos 입력값 보정 (범위 오류 방지)
		cosTheta = std::clamp(cosTheta, -1.0f, 1.0f);

		return std::acos(cosTheta);
	}

public:
	float x = 0.f;
	float y = 0.f;
};

using Vector2 = Vec2;