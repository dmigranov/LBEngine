#pragma once
#include <vector>

class Entity;
//todo: ������� MoveSystem/UpdateSystem - ��� ���������� ���������?
class System
{
public:
	System() {};
	virtual ~System() {};
	virtual void Execute() {};
protected:
	std::vector<Entity *> m_entities;;
};

