#pragma once
#include <vector>

class Entity;
//todo: ������� MoveSystem/UpdateSystem - ��� ���������� ���������?
class System
{
public:
	System() {};
	virtual ~System() {};
	virtual void Update() {};
protected:
	std::vector<Entity *> entities;;
};

