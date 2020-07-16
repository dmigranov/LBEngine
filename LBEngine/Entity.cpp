#include "pch.h"
#include "Entity.h"

#include "ComponentType.h"
#include "Component.h"
#include "TransformComponent.h"

Entity::Entity(const char* name) : 
	m_isActive(false)
{
	m_name = (nullptr == name) ? "Object" : name;

	//m_pTransform = new TransformComponent();
	//AddComponent(m_pTransform);

	m_pMesh = nullptr;
}

Entity::~Entity()
{
	for(auto pair : m_components)
	{
		if (pair.second != nullptr)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}
	m_components.clear();

	//mesh � transform �������� ��� �������� ���� �����������.
	//�� ��������� �� ������� ���������� ���, � ������?
	//���� ���������� ����� ���� ������
	//todo: smart ptr?
}

void Entity::Initialize()
{
	//todo
	/*if (m_pMesh != nullptr)
	{
		m_pMesh->Init();
	}

	if ( m_pEffect != nullptr)
	{
		m_pMaterial->Init();
	}*/
}

void Entity::AddComponent(const ComponentType type, Component* pComponent)
{
	m_components.insert(std::pair<ComponentType, Component*>(type, pComponent));
	pComponent->Initialize(this);

	std::bitset<COMPONENT_TYPE_COUNT> add = (size_t)1 << (size_t)type;
	m_componentsMask |= add;
}

void Entity::SetMesh(MeshComponent* pMesh)
{
	//todo: � ��� ������ �� ������? �������? todo: smart ptr
	m_pMesh = pMesh;
	AddComponent(ComponentType::MeshComponentType, pMesh);
}

void Entity::SetTransform(TransformComponent* pTransform)
{
	//todo: � ��� ������ �� ������? �������? todo: smart ptr
	m_pTransform = pTransform;
	AddComponent(ComponentType::TransformComponentType, pTransform);
}

TransformComponent* const Entity::GetTransform()
{
	return m_pTransform;
}

void Entity::Render()
{
	m_pMesh->Render(m_pTransform->GetWorld());
}

Component* Entity::GetComponent(ComponentType type)
{
	return m_components[type];
}

const std::bitset<COMPONENT_TYPE_COUNT>& Entity::GetComponentsMask()
{
	return m_componentsMask;
}
