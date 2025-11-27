#include "pch.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "Collider.h"
CollisionManager::CollisionManager()
{
	m_mapCollisionInfo.reserve(10000);
}
CollisionManager::~CollisionManager()
{
}
void CollisionManager::Update()
{
	for (UINT Row = 0; Row < (UINT)Layer::END; ++Row)
	{
		for (UINT Col = Row; Col < (UINT)Layer::END; ++Col)
		{
			if (m_objectLayer[Row] & (1 << Col))
			{
				CollisionLayerUpdate((Layer)Row, (Layer)Col);
			}
		}
	}
}

void CollisionManager::CheckLayer(Layer _left, Layer _right)
{
	// ???????? ?????? ?????.
	// ???? ???? LAYER?? ??????, ? ???? ??
	UINT Row = (UINT)_left;
	UINT Col = (UINT)_right;
	//Row = min(Row, Col);
	if (Row > Col)
		std::swap(Row, Col);
	//m_arrLayer[Row];
	//Col;

	//// ??? ????
	// ???? ???????
	if (m_objectLayer[Row] & (1 << Col))
	{
		// ?? ???
		m_objectLayer[Row] &= ~(1 << Col);
	}
	// ???? ????????r
	else
	{
		m_objectLayer[Row] |= (1 << Col);
	}
	int a = 0;
}

void CollisionManager::CheckReset()
{
	// ??? ????
	memset(m_objectLayer, 0, sizeof(UINT) * (UINT)Layer::END);
}

bool CollisionManager::IsCollisionLayer(Layer _left, Layer _right)
{
	UINT Row = (UINT)_left;
	UINT Col = (UINT)_right;
	if (Row > Col)
		std::swap(Row, Col);
	return (m_objectLayer[Row] & (1 << Col)) != 0;
}

void CollisionManager::SetCollisioned(Collider* pLeftCollider, Collider* pRightCollider)
{
	if (pRightCollider < pLeftCollider)
		std::swap(pLeftCollider, pRightCollider);
	COLLIDER_ID pairKey{pLeftCollider->GetID(), pRightCollider->GetID()};
	m_mapCollisionInfo.insert_or_assign(pairKey.ID, true);
	Object* pLeftObj = pLeftCollider->GetOwner();
	Object* pRightObj = pRightCollider->GetOwner();
	pLeftObj->EnterCollision(pRightCollider);
	pRightObj->EnterCollision(pLeftCollider);
}

void CollisionManager::RequestCollisionCheck(Collider* pLeftCollider, Collider* pRightCollider)
{
	if (IsCollision(pLeftCollider, pRightCollider))
	{
		SetCollisioned(pLeftCollider, pRightCollider);
	}
}

bool CollisionManager::BoxCast(Collider* collider, const Vec2 direction, const float maxDistance, const LayerMask layer, RaycastHit& outHit)
{
	if (nullptr == collider)
		return false;
	Vec2 origin = collider->GetWorldPos();
	Vec2 size = collider->GetSize();
	return BoxCast(origin, size, direction, maxDistance, layer, outHit);
}

bool CollisionManager::BoxCast(const Vec2 origin, const Vec2 size, const Vec2 direction, const float maxDistance, const LayerMask layermask, RaycastHit& outHit)
{

	std::shared_ptr<Scene> currentScene = GET_SINGLE(SceneManager)->GetCurScene();
	const vector<Object*>& layerObjects = currentScene->GetLayerObjects(layermask);

	float closestDistance = maxDistance;
	for (size_t i = 0; i < layerObjects.size(); ++i)
	{
		Collider* pLeftCollider = layerObjects[i]->GetComponent<Collider>();
		if (nullptr == pLeftCollider)
			continue;
		RaycastHit currentHit;
		if (BoxCast(origin, size, direction, maxDistance, pLeftCollider, currentHit))
		{
			float hitDistance = (currentHit.point - origin).Length();
			if (hitDistance < closestDistance)
			{
				closestDistance = hitDistance;
				outHit = currentHit;
			}
		}
	}
	return false;
}

bool CollisionManager::BoxCast(const Vec2 origin, const Vec2 size, const Vec2 direction, const float maxDistance, Collider* collider, RaycastHit& hit)
{
	if (nullptr == collider)
		return false;

	Vec2 targetSize = collider->GetSize();
	Vec2 targetPos = collider->GetWorldPos();

	Vec2 halfSize = size / 2.f;
	Vec2 targetHalf = targetSize / 2.f;

	Vec2 expandedMin = targetPos - targetHalf - halfSize;
	Vec2 expandedMax = targetPos + targetHalf + halfSize;

	Vec2 dir = direction;
	float dirLen = dir.Length();
	if (dirLen < FLT_EPSILON)
		return false;
	Vec2 dirN = dir / dirLen;

	float tMin = 0.f;
	float tMax = maxDistance;
	if (abs(dirN.x) < FLT_EPSILON)
	{
		if (origin.x < expandedMin.x || origin.x > expandedMax.x)
			return false;
	}
	else
	{
		float tx1 = (expandedMin.x - origin.x) / dirN.x;
		float tx2 = (expandedMax.x - origin.x) / dirN.x;
		float txMin = min(tx1, tx2);
		float txMax = max(tx1, tx2);
		tMin = max(tMin, txMin);
		tMax = min(tMax, txMax);
		if (tMin > tMax)
			return false;
	}

	if (fabsf(dirN.y) < FLT_EPSILON)
	{
		if (origin.y < expandedMin.y || origin.y > expandedMax.y)
			return false;
	}
	else
	{
		float ty1 = (expandedMin.y - origin.y) / dirN.y;
		float ty2 = (expandedMax.y - origin.y) / dirN.y;
		float tyMin = min(ty1, ty2);
		float tyMax = max(ty1, ty2);
		tMin = max(tMin, tyMin);
		tMax = min(tMax, tyMax);
		if (tMin > tMax)
			return false;
	}

	float hitDistance = (tMin >= 0.f) ? tMin : 0.f;
	if (hitDistance > maxDistance)
		return false;

	hit.collider = collider;
	hit.point = origin + dirN * hitDistance;

	return true;
}
void CollisionManager::CollisionLayerUpdate(Layer _left, Layer _right)
{
	std::shared_ptr<Scene> pCurrentScene = GET_SINGLE(SceneManager)->GetCurScene();
	const vector<Object*>& vecLeftLayer = pCurrentScene->GetLayerObjects(_left);
	const vector<Object*>& vecRightLayer = pCurrentScene->GetLayerObjects(_right);
	std::unordered_map<ULONGLONG, bool>::iterator iter;
	bool sameLayer = _left == _right;
	for (size_t i = 0; i < vecLeftLayer.size(); ++i)
	{
		Object* pLeftObj = vecLeftLayer[i];
		Collider* pLeftCollider = pLeftObj->GetComponent<Collider>();
		// 충돌체 없는 경우
		if (nullptr == pLeftCollider)
			continue;

		size_t jStart = 0;
		if (sameLayer)
			jStart = i + 1; // same layer: avoid duplicate pair checks and self-check

		for (size_t j = jStart; j < vecRightLayer.size(); ++j)
		{
			Object* pRightObj = vecRightLayer[j];
			Collider* pRightCollider = pRightObj->GetComponent<Collider>();
			// 충돌체가 없거나, 자기자신과의 충돌인 경우
			if (nullptr == pRightCollider || pLeftObj == pRightObj)
				continue;

			// 두 충돌체로만 만들 수 있는 ID
			ULONGLONG colliderID = MakePairKey(pLeftCollider->GetID(), pRightCollider->GetID());

			// try_emplace avoids a separate find+insert and returns iterator
			auto emplaceResult = m_mapCollisionInfo.try_emplace(colliderID, false);
			iter = emplaceResult.first;

			bool currentlyColliding = IsCollision(pLeftCollider, pRightCollider);

			// 캐시된 죽음 상태 확인 (호출 횟수 최소화)
			bool leftDead = pLeftObj->GetIsDead();
			bool rightDead = pRightObj->GetIsDead();

			if (currentlyColliding)
			{
				if (iter->second)
				{
					if (leftDead || rightDead)
					{
						pLeftCollider->ExitCollision(pRightCollider);
						pRightCollider->ExitCollision(pLeftCollider);
						iter->second = false;
					}
					else
					{
						pLeftCollider->StayCollision(pRightCollider);
						pRightCollider->StayCollision(pLeftCollider);
					}
				}
				else
				{
					if (!leftDead && !rightDead)
					{
						pLeftCollider->EnterCollision(pRightCollider);
						pRightCollider->EnterCollision(pLeftCollider);
						iter->second = true;
					}
				}
			}
			else
			{
				if (iter->second)
				{
					pLeftCollider->ExitCollision(pRightCollider);
					pRightCollider->ExitCollision(pLeftCollider);
					iter->second = false;
				}
			}
		}
	}
}

bool CollisionManager::IsCollision(Collider* _left, Collider* _right)
{
	const Vec2& leftPos = _left->GetWorldPos();
	const Vec2& rightPos = _right->GetWorldPos();
	const Vec2& leftSize = _left->GetSize();
	const Vec2& rightSize = _right->GetSize();

	float halfWidthSum = (leftSize.x + rightSize.x) * 0.5f;
	float halfHeightSum = (leftSize.y + rightSize.y) * 0.5f;
	float dx = fabsf(rightPos.x - leftPos.x);
	if (dx >= halfWidthSum)
		return false;
	float dy = fabsf(rightPos.y - leftPos.y);
	return dy < halfHeightSum;
}

ULONGLONG CollisionManager::MakePairKey(UINT a, UINT b)
{	COLLIDER_ID id = {};
	id.lo_ID = (a < b) ? a : b;
	id.hi_ID = (a < b) ? b : a;
	return id.ID;
}
