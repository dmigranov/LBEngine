#include "pch.h"
#include "CollisionComponent.h"
#include "..\inc\CollisionComponent.h"

using namespace DirectX::SimpleMath;

CollisionComponent::CollisionComponent(std::function<void(Entity*, Entity*, double)> func, double upleftX, double upleftY, double downrightX, double downrightY) : CollisionComponent(func, Vector2(upleftX, upleftY), Vector2(downrightX, downrightY))
{}

CollisionComponent::CollisionComponent(std::function<void(Entity*, Entity*, double)> func, double upleftX, double upleftY, double downrightX, double downrightY, bool isMovable) : CollisionComponent(func, upleftX, upleftY, downrightX, downrightY)
{
	m_isMovable = isMovable;
}

CollisionComponent::CollisionComponent(std::function<void(Entity*, Entity*, double)> func, DirectX::SimpleMath::Vector2 upleft, DirectX::SimpleMath::Vector2 downright)
{
	m_upleft = upleft;
	m_downright = downright;
	m_executeFunc = func;
}

CollisionComponent::CollisionComponent(std::function<void(Entity*, Entity*, double)> func, DirectX::SimpleMath::Vector2 upleft, DirectX::SimpleMath::Vector2 downright, bool isMovable) : CollisionComponent(func, upleft, downright)
{
	m_isMovable = isMovable;
}

bool CollisionComponent::IsMovable()
{
	return m_isMovable;
}
