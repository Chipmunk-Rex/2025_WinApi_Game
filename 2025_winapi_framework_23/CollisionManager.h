#pragma once
#include "Collider.h"
#include "CollisionManager.h"

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
struct CollisionInfo
{
	Collider* left = nullptr;
	Collider* right = nullptr;
	COLLIDER_ID id{};
	bool operator==(const CollisionInfo& other) const noexcept
	{
		return id.ID == other.id.ID;
	}
	bool operator!=(const CollisionInfo& other) const noexcept
	{
		return !(*this == other);
	}

	CollisionInfo(Collider* _left, Collider* _right, ULONGLONG _id)
		: left(_left), right(_right)
	{
		id.ID = _id;
	}
};
struct RaycastHit
{
	Collider* collider = nullptr;
	Vec2 point = Vec2();
	Vec2 normal = Vec2();
	float distance = 0.f;
};
class CollisionManager
{
	//CollisionManager();
	DECLARE_SINGLE_CD(CollisionManager);
public:
	void Update();
	void CheckLayer(Layer _left, Layer _right);
	void CheckReset();
	bool IsCollisionLayer(Layer _left, Layer _right);
	/// <summary>
	/// 강제로 충돌처리 요청
	/// </summary>
	void SetCollisioned(Collider* pLeftCollider, Collider* pRightCollider);
	void RequestCollisionCheck(Collider* pLeftCollider, Collider* pRightCollider);
	bool BoxCast(Collider* collider, const Vec2 direction, const float maxDistance, const LayerMask layer, RaycastHit& outHit);
	bool BoxCast(const Vec2 origin, const Vec2 size, const Vec2 direction, const float maxDistance, const LayerMask layer, RaycastHit& outHit);
private:
	bool BoxCast(const Vec2 origin, const Vec2 size, const Vec2 direction, const float maxDistance, Collider* collider, RaycastHit& outHit);
	void CollisionLayerUpdate(Layer _left, Layer _right);
	bool IsCollision(Collider* _left, Collider* _right);
	ULONGLONG MakePairKey(UINT a, UINT b);
private:
	// 그룹 간의 충돌체크 배열
	UINT m_objectLayer[(UINT)Layer::END];
	std::unordered_map<ULONGLONG, CollisionInfo> m_CollisionInfo;
};
