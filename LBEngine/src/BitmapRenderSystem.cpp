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
