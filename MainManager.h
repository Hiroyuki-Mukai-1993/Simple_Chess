#pragma once

#include<DxLib.h>
#include"InputManager.h"
#include"LoadManager.h"
#include"DrawManager.h"
#include"Board.h"
#include"Game.h"

class MainManager
{
private:
	InputManager* m_input;
	LoadManager* m_load;
	DrawManager* m_draw;
	Board* m_board;
	Game* m_game;

	game_signal m_signal;
public:
	MainManager();
	~MainManager();

	void MainLoop();
};

