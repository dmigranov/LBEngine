#include "pch.h"
#include "PhysicsSystem.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"

#include "CollisionComponent.h"

#include "Entity.h"

using namespace DirectX::SimpleMath;

PhysicsSystem::PhysicsSystem()
{
	SubscribeToComponentType(ComponentType::TransformComponentType);
	SubscribeToComponentType(ComponentType::PhysicsComponentType);

	//todo: ��������� � ��������� ������� � ���������� �� �����������
	SubscribeToComponentType(ComponentType::CollisionComponentType);
}

void PhysicsSystem::Execute(DWORD deltaMillis)
{

	double deltaTime = deltaMillis / 1000.;
	for (auto pEntity : m_entities)
	{
		TransformComponent* transform = (TransformComponent*)pEntity->GetComponent(ComponentType::TransformComponentType);
		PhysicsComponent* physics = (PhysicsComponent*)pEntity->GetComponent(ComponentType::PhysicsComponentType);

		auto forces = physics->m_forces;

		auto resultForce = Vector3::Zero;
		for(auto pair : forces)
		{
			resultForce += pair.second;
		}
		
		auto mass = physics->m_mass;
		if(mass > 0)
		{ 
			auto acceleration = resultForce / mass;
			physics->m_acceleration = acceleration;

			auto velocity = physics->m_velocity + acceleration * deltaTime;
			physics->m_velocity = velocity;

			transform->Move(velocity * deltaTime);

		}
	}

	//todo ��������: ����� ��������� � CollisionSystem (����� PhysicsSystem �� ����� �������� �� CollisionComponent)

	for (auto pEntityFirst : m_entities)
	{
		for (auto pEntitySecond : m_entities)
		{
			//todo: ��������, ������������� �� ����� ����� ����������, ����� ��� ���������� (��������� ��)...
			if (pEntityFirst != pEntitySecond)
			{

			}
		}
	}
}
