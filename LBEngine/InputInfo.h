#pragma once
class InputInfo
{
public:
	//todo: ������� ���� ������� � �� ������ ������� ��������� �� � ����������� �� DXTK-����
	//static void Update();
	DirectX::Keyboard::State& GetKeys();
private:
	static DirectX::Keyboard  m_keyboard;
	static DirectX::Mouse     m_mouse;
};

