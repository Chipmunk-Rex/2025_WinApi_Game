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
				//int a = 0;
				CollisionLayerUpdate((Layer)Row, (Layer)Col);
			}
		}
	}
}

void CollisionManager::CheckLayer(Layer _left, Layer _right)
{
	// �������� ������ ���ô�.
	// ���� ���� LAYER�� ������, ū ���� ��
	UINT Row = (UINT)_left;
	UINT Col = (UINT)_right;
	//Row = min(Row, Col);
	if (Row > Col)
		std::swap(Row, Col);
	//m_arrLayer[Row];
	//Col;

	//// ��Ʈ ����
	// üũ�� �Ǿ��ִٸ�
	if (m_objectLayer[Row] & (1 << Col))
	{
		// üũ Ǯ��
		m_objectLayer[Row] &= ~(1 << Col);
	}
	// üũ�� �ȵǾ��ִٸ�r
	else
	{
		m_objectLayer[Row] |= (1 << Col);
	}
	int a = 0;
}

void CollisionManager::CheckReset()
{
	// �޸� �ʱ�ȭ
	memset(m_objectLayer, 0, sizeof(UINT) * (UINT)Layer::END);
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
		// �浹ü ���� ���
		if (nullptr == pLeftCollider)
			continue;
		for (size_t j = 0; j < vecRightLayer.size(); j++)
		{
			Collider* pRightCollider = vecRightLayer[j]->GetComponent<Collider>();
			// �浹ü�� ���ų�, �ڱ��ڽŰ��� �浹�� ���
			if (nullptr == pRightCollider || vecLeftLayer[i] == vecRightLayer[j])
				continue;

			// �� �浹ü�θ� ���� �� �ִ� ID
			ULONGLONG colliderID = MakePairKey(pLeftCollider->GetID(), pRightCollider->GetID());

			iter = m_mapCollisionInfo.find(colliderID);
			// ���� ������ �浹�� �� ����.
			if (iter == m_mapCollisionInfo.end())
			{
				// �浹 ������ �̵�ϵ� ������ ��� ���(�浹���� �ʾҴٷ�)
				m_mapCollisionInfo.insert({ colliderID, false });
				//m_mapCollisionInfo[colliderID.ID] = false;
				iter = m_mapCollisionInfo.find(colliderID);
			}

			// �浹���� Ȯ��
			if (IsCollision(pLeftCollider, pRightCollider))
			{
				// �������� �浹��
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
				else // ������ �浹 x
				{
					if (!vecLeftLayer[i]->GetIsDead() && !vecRightLayer[j]->GetIsDead())
					{
						pLeftCollider->EnterCollision(pRightCollider);
						pRightCollider->EnterCollision(pLeftCollider);
						iter->second = true;
					}
				}
			}
			else // �浹 ���ϳ�?
			{
				if (iter->second) // �ٵ� ������ �浹��
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
	// �¿� ������ ���ǹ��ϰ�: ���� ���� lo, ū ���� hi
	COLLIDER_ID id = {};
	id.lo_ID = (a < b) ? a : b;
	id.hi_ID = (a < b) ? b : a;
	return id.ID;
}
