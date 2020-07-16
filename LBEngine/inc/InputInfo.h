#pragma once
class InputInfo
{
public:
	InputInfo();
	//todo: ������� ���� ������� � �� ������ ������� ��������� �� � ����������� �� DXTK-����
	//static void Update();
	//DirectX::Keyboard::State GetKeys();
	bool IsKeyPressed(DirectX::Keyboard::Keys key);
private:
	std::unique_ptr<DirectX::Keyboard>  m_keyboard;
	std::unique_ptr<DirectX::Mouse>     m_mouse;
};

