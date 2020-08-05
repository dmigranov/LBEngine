#include "pch.h"
#include "CollisionSystem.h"
#include "CollisionComponent.h"
#include "TransformComponent.h"

#include "Entity.h"

using namespace DirectX::SimpleMath;

CollisionSystem::CollisionSystem()
{
	SubscribeToComponentType(ComponentType::CollisionComponentType);
	SubscribeToComponentType(ComponentType::TransformComponentType);

}

void CollisionSystem::Execute(DWORD deltaTime)
{
	//todo: ��������������: 
	//��� ����� ��������� ������� �� ������������ ���� � ������. 
	//������� ������ ���������� ��������?
	//
	for (auto i = m_entities.begin(); i != m_entities.end(); ++i) {
		for (auto j = i; ++j != m_entities.end(); /**/) {
			auto pEntity1 = *i;
			auto pEntity2 = *j;

			bool areCollided = CheckCollision(pEntity1, pEntity2);
		}
	}
}

bool CollisionSystem::CheckCollision(Entity* pEntity1, Entity* pEntity2)
{
	CollisionComponent* pCollision1 = (CollisionComponent*)pEntity1->GetComponent(ComponentType::CollisionComponentType);
	CollisionComponent* pCollision2 = (CollisionComponent*)pEntity2->GetComponent(ComponentType::CollisionComponentType);

	TransformComponent* pTransform1 = (TransformComponent*)pEntity1->GetComponent(ComponentType::TransformComponentType);
	TransformComponent* pTransform2 = (TransformComponent*)pEntity2->GetComponent(ComponentType::TransformComponentType);

	auto ul1 = pCollision1->m_upleft, dr1 = pCollision1->m_downright;
	auto ul2 = pCollision2->m_upleft, dr2 = pCollision2->m_downright;

	auto pos1_3D = pTransform1->GetPosition();
	auto pos1_2D = Vector2(pos1_3D.x, pos1_3D.y);
	auto pos2_3D = pTransform2->GetPosition();
	auto pos2_2D = Vector2(pos2_3D.x, pos2_3D.y);

	//todo: ������� �� �������� (�.� ����� �������������� ����); ������� ����)
	auto worldUL1 = ul1 + pos1_2D;
	auto worldDR1 = dr1 + pos1_2D;
	auto worldUL2 = ul2 + pos2_2D;
	auto worldDR2 = dr2 + pos2_2D;

	//todo

	return false;
}
