#pragma once

#include <typeindex>

class ComponentTypeManager
{
public:
	template<typename T> void RegisterComponentType()
	{
		if(m_typeAdditionPossible)
		{
			m_componentTypes.insert(m_componentTypes.begin(), typeid(T));
		}
	}

	void SetTypeAdditionEnded();

	int GetComponentTypesCount();

private:
	bool m_typeAdditionPossible = true;
	std::vector<std::type_index> m_componentTypes;

	int m_componentTypesCount = 0;
};