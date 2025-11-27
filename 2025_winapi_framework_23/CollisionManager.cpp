#include "pch.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "Collider.h"
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

bool CollisionManager::BoxCast(Collider* collider, const Vec2 direction, const float maxDistance, const LayerMask layer, LaycastHit& outHit)
{
	if (nullptr == collider)
		return false;
	Vec2 origin = collider->GetWorldPos();
	Vec2 size = collider->GetSize();
	return BoxCast(origin, size, direction, maxDistance, layer, outHit);
}

bool CollisionManager::BoxCast(const Vec2 origin, const Vec2 size, const Vec2 direction, const float maxDistance, const LayerMask layermask, LaycastHit& outHit)
{

	std::shared_ptr<Scene> currentScene = GET_SINGLE(SceneManager)->GetCurScene();
	const vector<Object*>& layerObjects = currentScene->GetLayerObjects(layermask);

	float closestDistance = maxDistance;
	for (size_t i = 0; i < layerObjects.size(); ++i)
	{
		Collider* pLeftCollider = layerObjects[i]->GetComponent<Collider>();
		if (nullptr == pLeftCollider)
			continue;
		LaycastHit currentHit;
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

bool CollisionManager::BoxCast(const Vec2 origin, const Vec2 size, const Vec2 direction, const float maxDistance, Collider* collider, LaycastHit& hit)
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
	for (size_t i = 0; i < vecLeftLayer.size(); ++i)
	{
		Collider* pLeftCollider = vecLeftLayer[i]->GetComponent<Collider>();
		// 충돌체 없는 경우
		if (nullptr == pLeftCollider)
			continue;
		for (size_t j = 0; j < vecRightLayer.size(); j++)
		{
			Collider* pRightCollider = vecRightLayer[j]->GetComponent<Collider>();
			// 충돌체가 없거나, 자기자신과의 충돌인 경우
			if (nullptr == pRightCollider || vecLeftLayer[i] == vecRightLayer[j])
				continue;

			// 두 충돌체로만 만들 수 있는 ID
			ULONGLONG colliderID = MakePairKey(pLeftCollider->GetID(), pRightCollider->GetID());

			iter = m_mapCollisionInfo.find(colliderID);
			// 이전 프레임 충돌한 적 없다.
			if (iter == m_mapCollisionInfo.end())
			{
				// 충돌 정보가 미등록된 상태인 경우 등록(충돌하지 않았다로)
				m_mapCollisionInfo.insert({ colliderID, false });
				//m_mapCollisionInfo[colliderID.ID] = false;
				iter = m_mapCollisionInfo.find(colliderID);
			}

			// 충돌여부 확인
			if (IsCollision(pLeftCollider, pRightCollider))
			{
				// 이전에도 충돌중
				if (iter->second)
				{
					if (vecLeftLayer[i]->GetIsDead() || vecRightLayer[j]->GetIsDead())
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
				else // 이전에 충돌 x
				{
					if (!vecLeftLayer[i]->GetIsDead() && !vecRightLayer[j]->GetIsDead())
					{
						pLeftCollider->EnterCollision(pRightCollider);
						pRightCollider->EnterCollision(pLeftCollider);
						iter->second = true;
					}
				}
			}
			else // 충돌 안하네?
			{
				if (iter->second) // 근데 이전에 충돌중
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
	Vec2 leftPos = _left->GetWorldPos();
	Vec2 rightPos = _right->GetWorldPos();
	Vec2 leftSize = _left->GetSize();
	Vec2 rightSize = _right->GetSize();

	return (fabsf(rightPos.x - leftPos.x) < (leftSize.x + rightSize.x) / 2.f
		&& fabsf(rightPos.y - leftPos.y) < (leftSize.y + rightSize.y) / 2.f);
}

ULONGLONG CollisionManager::MakePairKey(UINT a, UINT b)
{
	// ?¿? ?????? ????????: ???? ???? lo, ? ???? hi
	COLLIDER_ID id = {};
	id.lo_ID = (a < b) ? a : b;
	id.hi_ID = (a < b) ? b : a;
	return id.ID;
}
