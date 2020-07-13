#include "pch.h"
#include "Scene.h"

#include "Entity.h"
#include "System.h"
#include "Camera.h"


Scene::Scene() : m_pCamera(nullptr)
{}

Scene::~Scene()
{
	//�������� ��������...
}

void Scene::AddEntity(Entity* pEntity)
{
	if (pEntity == nullptr)
	{
		return;
	}
	pEntity->Initialize();
	m_entities.push_back(pEntity);
}

void Scene::SetCamera(Camera* pCamera)
{
	if (pCamera != nullptr)
	{
		m_pCamera = pCamera;
	}
}

Camera* Scene::GetCamera()
{
	return m_pCamera;
}

void Scene::Update()
{
	//m_pCamera->GetObjectPtr()->Update();


	for (auto pSystem : m_systems)
	{
		if (pSystem != nullptr)
		{
			pSystem->Execute();
		}
	}
}
