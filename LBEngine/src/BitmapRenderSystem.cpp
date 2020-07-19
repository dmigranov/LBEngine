#include "pch.h"
#include "BitmapRenderSystem.h"
#include "BitmapComponent.h"
#include "Entity.h"

void BitmapRenderSystem::Execute(DWORD deltaTime)
{
	//todo: sort

	for (auto pEntity : m_entities)
	{
		BitmapComponent* bitmapComponent = (BitmapComponent*)pEntity->GetComponent(ComponentType::BitmapComponentType);
		//todo: ������ render


		//todo: � ������� ���������� � ���������� �� ������������ �� MeshComponent
	}
}

void BitmapRenderSystem::AddEntity(Entity* pEntity)
{
	BitmapComponent* bitmapComponent = (BitmapComponent*)pEntity->GetComponent(ComponentType::BitmapComponentType);

	if(bitmapComponent->IsOpaque())
	m_entities.push_back(pEntity);

}
