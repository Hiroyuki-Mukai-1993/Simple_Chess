#pragma once

#include<DxLib.h>
#include<stdlib.h>
#include"InputManager.h"
#include"LoadManager.h"
#include"Board.h"
#include"Game.h"

class DrawManager
{
private:
public:
	void draw_main(InputManager*,LoadManager*,Board*,game_signal,game_turn);

	void draw_board(LoadManager*);

	void draw_piece(LoadManager*,Board*);

	void draw_focus(InputManager*, int);

	void draw_promotion_menu(LoadManager*,game_turn);

	void draw_result(game_signal,game_turn);

	void draw_test(InputManager*,Board*);
};

