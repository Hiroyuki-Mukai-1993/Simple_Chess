#pragma once

#include<DxLib.h>

class InputManager
{
private:
	int m_mouseX, m_mouseY;
	int m_mouseInputState;
	int m_mouseInputLogType;
public:
	InputManager();

	void updateInput();

	const int get_mouseX();
	const int get_mouseY();
	const int get_mouseInputState();
	const int get_mouseInputLogType();
};

