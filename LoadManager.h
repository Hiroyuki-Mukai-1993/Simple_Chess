#pragma once

#include<DXLib.h>

class LoadManager
{
private:
	int m_piece[2][6];
	int m_board[2];
	int m_focus;
	int m_promotionMenu;
public:
	LoadManager();

	const int get_piece(const int, const int);
	const int get_board(const int);
	const int get_focus();
	const int get_promotionMenu();
};

