#pragma once
#include "Component.h"
class CollisionComponent :
    public Component
{
public:
    //todo: ������� ����������� � ������� � ������� � ������� ��?
    CollisionComponent(std::function<void(Entity*, Entity*, double)> func, double upleftX, double upleftY, double downrightX, double downrightY);
    CollisionComponent(std::function<void(Entity*, Entity*, double)> func, double upleftX, double upleftY, double downrightX, double downrightY, bool isMovable);
    CollisionComponent(std::function<void(Entity*, Entity*, double)> func, DirectX::SimpleMath::Vector2 upleft, DirectX::SimpleMath::Vector2 downright);
    CollisionComponent(std::function<void(Entity*, Entity*, double)> func, DirectX::SimpleMath::Vector2 upleft, DirectX::SimpleMath::Vector2 downright, bool isMovable);

    bool IsMovable();
private:
    friend class CollisionSystem;

    std::function<void(Entity*, Entity*, double)> m_executeFunc;

    //AABB - axis-aligned bounding box
    DirectX::SimpleMath::Vector2 m_upleft, m_downright; //m_upright, m_downleft, - ���������

    bool m_isMovable = false;
};

