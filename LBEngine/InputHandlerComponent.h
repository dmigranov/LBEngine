#pragma once
#include "Component.h"

#include <functional>

class InputInfo;

class InputHandlerComponent :
    public Component
{
public:

    //todo: ���-�� ����� �� �������� � InputHandler: ������� �����
    //����� ������.
    //����� ������� InputSystem, �������� ������� �������� ������...
    InputHandlerComponent(std::function<void(Entity *, InputInfo)> func);
private:
    std::function<void(Entity*, InputInfo)> m_inputHandlerFunc;
};

