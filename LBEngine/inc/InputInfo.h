#pragma once
class InputInfo
{
public:
	InputInfo();
	//todo: ������� ���� ������� � �� ������ ������� ��������� �� � ����������� �� DXTK-����
	//static void Update();
	//DirectX::Keyboard::State GetKeys();
	//bool IsKeyPressed(DirectX::Keyboard::Keys key);
private:
	friend class InputSystem;

	void Update();
};

