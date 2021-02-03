#include "InputManager.h"

InputManager::InputManager() {
	SetMouseDispFlag(true);

	m_mouseX = 0, m_mouseY = 0;
	m_mouseInputState = 0;
	m_mouseInputLogType = 1;
}

void InputManager::updateInput() {
	GetMouseInputLog2(&m_mouseInputState, &m_mouseX, &m_mouseY, &m_mouseInputLogType);
}

const int InputManager::get_mouseX() {
	return m_mouseX;
}

const int InputManager::get_mouseY() {
	return m_mouseY;
}

const int InputManager::get_mouseInputState() {
	return m_mouseInputState;
}

const int InputManager::get_mouseInputLogType() {
	return m_mouseInputLogType;
}