#include "MainManager.h"

MainManager::MainManager() {
	ChangeWindowMode(true);

	m_input = new InputManager;
	m_load = new LoadManager;
	m_draw = new DrawManager;
	m_board = new Board;
	m_game = new Game;

	m_signal = SIGNAL_NONE;
}

MainManager::~MainManager() {
	delete m_input;
	delete m_load;
	delete m_draw;
	delete m_game;
	delete m_board;
}

void MainManager::MainLoop() {
	while (1) {
		m_input->updateInput();
		
		m_signal=m_game->Proceed(m_input, m_board);

		m_draw->draw_main(m_input,m_load,m_board,m_signal,m_game->get_turn());

		if (m_input->get_mouseInputState() == MOUSE_INPUT_RIGHT)	break;
	}
}