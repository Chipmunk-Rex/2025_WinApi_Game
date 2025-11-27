#pragma once
union COLLIDER_ID
{
	struct
	{
		UINT lo_ID;
		UINT hi_ID;
	};
	ULONGLONG ID;
};
class Collider;
struct LaycastHit
{
	Collider* collider = nullptr;
	Vec2 point = Vec2();
	float distance = 0.f;
};
class CollisionManager
{
	DECLARE_SINGLE(CollisionManager);
public:
	void Update();
	void CheckLayer(Layer _left, Layer _right);
	void CheckReset();
	bool IsCollisionLayer(Layer _left, Layer _right);
	bool BoxCast(Collider* collider, const Vec2 direction, const float maxDistance, const LayerMask layer, LaycastHit& outHit);
	bool BoxCast(const Vec2 origin, const Vec2 size, const Vec2 direction, const float maxDistance, const LayerMask layer, LaycastHit& outHit);
private:
	bool BoxCast(const Vec2 origin, const Vec2 size, const Vec2 direction, const float maxDistance, Collider* collider, LaycastHit& outHit);
	void CollisionLayerUpdate(Layer _left, Layer _right);
	bool IsCollision(Collider* _left, Collider* _right);
	ULONGLONG MakePairKey(UINT a, UINT b);
private:
	// 그룹 간의 충돌체크 배열
	UINT m_objectLayer[(UINT)Layer::END];
	std::unordered_map<ULONGLONG, bool> m_mapCollisionInfo;
};
