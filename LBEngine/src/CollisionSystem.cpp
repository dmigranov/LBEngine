#include "pch.h"
#include "CollisionSystem.h"

#include "CollisionComponent.h"
#include "AABBCollisionComponent.h"
#include "CircleCollisionComponent.h"

#include "CollisionComponentType.h"

#include "PhysicsComponent.h"
#include "TransformComponent.h"

#include "ContactManifold.h"

#include "Entity.h"

using namespace DirectX::SimpleMath;

CollisionSystem::CollisionSystem()
{
	SubscribeToComponentType(ComponentType::CollisionComponentType);
	SubscribeToComponentType(ComponentType::PhysicsComponentType);
	SubscribeToComponentType(ComponentType::TransformComponentType);
}

void CollisionSystem::Execute(double deltaTime)
{
	//todo: �������� ������ (����������������) ����?
	//���� ��� ����� ���������, ��������, ���� �� ������������ ���� � ������
	//� �����, ������ ������� ���� ��-������, � ������ ������ ������?

	for (auto pMovable: m_movableEntities) {
		for (auto e: m_entities) {
			if (pMovable != e)
			{
				ContactManifold cm(pMovable, e);
				bool areCollided = CheckCollision(cm);

				if (areCollided)
				{
					CollisionComponent* pCollision1 = (CollisionComponent*)pMovable->GetComponent(ComponentType::CollisionComponentType);
					CollisionComponent* pCollision2 = (CollisionComponent*)e->GetComponent(ComponentType::CollisionComponentType);
					PhysicsComponent* pPhysics1 = (PhysicsComponent*)pMovable->GetComponent(ComponentType::PhysicsComponentType);
					PhysicsComponent* pPhysics2 = (PhysicsComponent*)e->GetComponent(ComponentType::PhysicsComponentType);

					//todo: calculate normal and penetration

					//Resolve Collision
					//if(��� �����������)
					//	���������� �� �����?
					Vector3 relativeV = pPhysics1->GetVelocity() - pPhysics1->GetVelocity();

					//todo: ������� �����: �������� ������ �� ContactManifold � ��������� (����������) ���-�������

					pCollision1->m_executeFunc(pMovable, e, deltaTime);
					pCollision2->m_executeFunc(e, pMovable, deltaTime);
				}
			}
		}
	}
}

void CollisionSystem::AddEntity(Entity* pEntity)
{
	CollisionComponent* pCollision = (CollisionComponent*)pEntity->GetComponent(ComponentType::CollisionComponentType);

	if (pCollision->IsMovable())
		m_movableEntities.push_back(pEntity);
	
	System::AddEntity(pEntity);
}

bool CollisionSystem::CheckCollision(ContactManifold& resultContactManifold)
{
	auto pEntity1 = resultContactManifold.m_pEntity1, pEntity2 = resultContactManifold.m_pEntity2;
	bool areCollided = false;

	CollisionComponent* pCollision1 = (CollisionComponent*)pEntity1->GetComponent(ComponentType::CollisionComponentType);
	CollisionComponent* pCollision2 = (CollisionComponent*)pEntity2->GetComponent(ComponentType::CollisionComponentType);

	TransformComponent* pTransform1 = (TransformComponent*)pEntity1->GetComponent(ComponentType::TransformComponentType);
	TransformComponent* pTransform2 = (TransformComponent*)pEntity2->GetComponent(ComponentType::TransformComponentType);

	CollisionComponentType type1 = pCollision1->GetType(), type2 = pCollision2->GetType();
	
	if (type1 == CollisionComponentType::AAABCollisionComponentType && type2 == CollisionComponentType::AAABCollisionComponentType)
		areCollided = CheckDoubleAABBCollision(static_cast<AABBCollisionComponent*>(pCollision1), static_cast<AABBCollisionComponent*>(pCollision2), pTransform1, pTransform2);
	else if (type1 == CollisionComponentType::CircleCollisionComponentType && type2 == CollisionComponentType::CircleCollisionComponentType)
		areCollided = CheckDoubleCircleCollision(static_cast<CircleCollisionComponent*>(pCollision1), static_cast<CircleCollisionComponent*>(pCollision2), pTransform1, pTransform2);
	else
		; //areCollided = CheckAABBCircleCollision(static_cast<AABBCollisionComponent*>(pCollision1), static_cast<CircleCollisionComponent*>(pCollision2), pTransform1, pTransform2);
	return areCollided;
}

bool CollisionSystem::CheckDoubleAABBCollision(AABBCollisionComponent* pAABB1, AABBCollisionComponent* pAABB2, TransformComponent* pTransform1, TransformComponent* pTransform2)
{
	auto ul1 = pAABB1->m_upleft, dr1 = pAABB1->m_downright;
	auto ul2 = pAABB2->m_upleft, dr2 = pAABB2->m_downright;

	auto pos1_3D = pTransform1->GetPosition();
	auto pos1_2D = Vector2(pos1_3D.x, pos1_3D.y);

	auto pos2_3D = pTransform2->GetPosition();
	auto pos2_2D = Vector2(pos2_3D.x, pos2_3D.y);

	auto worldUL1 = ul1 + pos1_2D;
	auto worldDR1 = dr1 + pos1_2D;
	auto worldUL2 = ul2 + pos2_2D;
	auto worldDR2 = dr2 + pos2_2D;

	if (worldUL1.x < worldDR2.x &&
		worldDR1.x > worldUL2.x &&
		worldUL1.y < worldDR2.y &&
		worldDR1.y > worldUL2.y) 
		return true;

	return false;
}

bool CollisionSystem::CheckDoubleCircleCollision(CircleCollisionComponent* pCircle1, CircleCollisionComponent* pCircle2, TransformComponent* pTransform1, TransformComponent* pTransform2)
{
	auto pos1_3D = pTransform1->GetPosition(), pos2_3D = pTransform2->GetPosition();
	auto pos1_2D = Vector2(pos1_3D.x, pos1_3D.y), pos2_2D = Vector2(pos2_3D.x, pos2_3D.y);
	auto worldCentre1 = pCircle1->m_centre + pos1_2D;
	auto worldCentre2 = pCircle2->m_centre + pos2_2D;

	double r1 = pCircle1->m_radius, r2 = pCircle2->m_radius;
	double r = r1 + r2;
	r *= r;
	return r < pow(worldCentre1.x + worldCentre2.x, 2.) + pow(worldCentre1.y + worldCentre2.y, 2.);
}
