#include "pch.h"
#include "ComponentTypeManager.h"



void ComponentTypeManager::SetTypeAdditionEnded()
{
    m_typeAdditionPossible = false;
    //todo: ������� ������ �� ������� (�� ������ ������)
}

int ComponentTypeManager::GetComponentTypesCount()
{
    return m_componentTypes.size();
}
