#pragma once
#include "Component.h"

#include <functional>

class InputHandlerComponent :
    public Component
{
public:
    class InputInfo
    {

    };

    //todo: ���-�� ����� �� �������� � InputHandler: ������� �����
    //����� ������.
    //����� ������� InputSystem, �������� ������� �������� ������...
    InputHandlerComponent(std::function<void(Entity *, InputInfo)> func);
private:
    std::function<void(Entity*, InputInfo)> m_inputHandlerFunc;
};

