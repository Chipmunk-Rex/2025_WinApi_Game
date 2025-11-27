#include "pch.h"
#include "Rigidbody.h"
#include "Object.h"
#include "CollisionManager.h"
#include "Collider.h"
Rigidbody::Rigidbody()
	: m_mass(1.f)                // 질량 (1~5)
	, m_friction(2.5f)           // 지면 마찰
	, m_force(0.f, 0.f)          // 누적 힘
	, m_airDrag(0.f)            // 공중 감속
	, m_useGravity(false)         // 중력 사용 여부
	, m_isKinematic(false)       // 키네마틱 여부
	, continiuousCollision(false) // 연속 충돌 검사 여부
	, m_bounciness(0.f)          // 탄성력
	, m_velocity(0.f, 0.f)       // 현재 속도
	, m_maxVelocity(1000.f, 1000.f) // 속도 제한 (x, y)
	, m_gravity(0.f, 400.f)      // 중력 가속도
	, m_accelation(0.f, 0.f)     // 가속도
	, m_grounded(false)          // 접지 여부
{
}
Rigidbody::~Rigidbody()
{
}

void Rigidbody::Init()
{
}

void Rigidbody::LateUpdate()
{
}

void Rigidbody::FixedUpdate(float _fixedDT)
{
	if (m_isKinematic)
	{
		m_force = { 0.f,0.f };
		return;
	}
	// 힘 -> 가속도
	m_accelation = m_force / m_mass;
	m_velocity += m_accelation * _fixedDT;

	// 중력 적용
	if (m_useGravity)
	{
		if (!m_grounded)
			m_velocity += m_gravity * _fixedDT;
		else
			m_velocity.y = 0.f;
	}

	// 감속 처리
	if (m_velocity.Length() > 0.f)
	{
		if (m_grounded)
		{
			// 바닥 마찰
			float frictionAmount = m_friction * _fixedDT;
			m_velocity.x = std::lerp(m_velocity.x, 0.f, frictionAmount);
		}
		else
		{
			// 공중 감속
			float dragAmount = m_airDrag * _fixedDT;
			m_velocity.x = std::lerp(m_velocity.x, 0.f, dragAmount);
		}
	}

	// 속도 제한(축 기준 단순화)
	m_velocity.x = std::clamp(m_velocity.x, -m_maxVelocity.x, m_maxVelocity.x);
	m_velocity.y = std::clamp(m_velocity.y, -m_maxVelocity.y, m_maxVelocity.y);

	ApplyMovement(_fixedDT);

	// 힘은 한번 처리하고 초기화, 1프레임 단위로 유효
	m_force = Vec2(0.f, 0.f);
}

void Rigidbody::ApplyMovement(float _fixedDT)
{
	Object* owner = GetOwner();
	Vec2 pos = owner->GetPos();

	static int callStackCount;
	if (callStackCount > 15)
	{
		callStackCount = 0;

		pos += m_velocity * _fixedDT;
		owner->SetPos(pos);
		return;
	}

	if (continiuousCollision)
	{
		Collider* col = owner->GetComponent<Collider>();
		if (col)
		{
			auto collisionManager = GET_SINGLE(CollisionManager);
			Layer ownerLayer = owner->GetLayer();

			float velLen = m_velocity.Length();
			if (velLen > FLT_EPSILON)
			{
				// 충돌 마스크 구성
				LayerMask collisionMask = 0;
				for (int i = 0; i < (int)Layer::END; ++i)
				{
					if (collisionManager->IsCollisionLayer(ownerLayer, (Layer)i))
						collisionMask |= (1u << i);
				}

				Vec2 normalizedDirection = { m_velocity.x / velLen, m_velocity.y / velLen };

				RaycastHit hit;
				collisionManager->BoxCast(col, normalizedDirection, velLen * _fixedDT, collisionMask, hit);
				if (hit.collider)
				{
					GET_SINGLE(CollisionManager)->SetCollisioned(col, hit.collider);
					// 충돌 지점까지 이동
					float distanceToHit = (hit.point - pos).Length();
					pos += normalizedDirection * distanceToHit;
					owner->SetPos(pos);

					// 남은 이동 거리 계산
					float totalMoveDist = velLen * _fixedDT;
					float remainingDist = totalMoveDist - distanceToHit;
					if (remainingDist > FLT_EPSILON)
					{
						// Projectile 스타일의 축 반사 적용
						if (m_bounciness > 0.f)
						{
							Object* otherOwner = hit.collider->GetOwner();
							// 상대 물체 중심과 크기 기반으로 어느 축 충돌인지 판단
							float distanceX = fabs(otherOwner->GetPos().x - owner->GetPos().x);
							float distanceY = fabs(otherOwner->GetPos().y - owner->GetPos().y);

							float deltaX = distanceX - (hit.collider->GetSize().x / 2.f);
							float deltaY = distanceY - (hit.collider->GetSize().y / 2.f);

							Vec2 v = m_velocity;
							if (deltaX > deltaY)
								v = Vec2(-v.x, v.y);
							else
								v = Vec2(v.x, -v.y);

							// 탄성 계수 적용
							m_velocity = v * m_bounciness;

							// 남은 시간으로 재귀 이동
							float newVelLen = m_velocity.Length();
							if (newVelLen > FLT_EPSILON)
							{
								float remainingDT = remainingDist / newVelLen;
								if (remainingDT > FLT_EPSILON) 
								{
									callStackCount++;
									ApplyMovement(remainingDT);
								}
							}
						}
						else
						{
							// 탄성 없음: 즉시 정지
							m_velocity = Vec2(0.f, 0.f);
						}
					}
					callStackCount = 0;
					return; // 충돌 처리 후 종료
				}
			}
		}
	}

	// 충돌이 없으면 일반 이동
	pos += m_velocity * _fixedDT;
	owner->SetPos(pos);

	callStackCount = 0;
}

void Rigidbody::Render(HDC hDC)
{
}
////////////////////

////