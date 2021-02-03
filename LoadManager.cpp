#include "LoadManager.h"

LoadManager::LoadManager() {
	m_piece[0][0] = LoadGraph("img/white_king.png");
	m_piece[0][1] = LoadGraph("img/white_queen.png");
	m_piece[0][2] = LoadGraph("img/white_rook.png");
	m_piece[0][3] = LoadGraph("img/white_bishiop.png");
	m_piece[0][4] = LoadGraph("img/white_knight.png");
	m_piece[0][5] = LoadGraph("img/white_pawn.png");
	m_piece[1][0] = LoadGraph("img/black_king.png");
	m_piece[1][1] = LoadGraph("img/black_queen.png");
	m_piece[1][2] = LoadGraph("img/black_rook.png");
	m_piece[1][3] = LoadGraph("img/black_bishiop.png");
	m_piece[1][4] = LoadGraph("img/black_knight.png");
	m_piece[1][5] = LoadGraph("img/black_pawn.png");

	m_board[0] = LoadGraph("img/white.png");
	m_board[1] = LoadGraph("img/black.png");

	m_focus = LoadGraph("img/focus.png");

	m_promotionMenu = LoadGraph("img/promotion_menu.png");
}

const int LoadManager::get_piece(const int i, const int j) {
	return m_piece[i][j];
}

const int LoadManager::get_board(int i) {
	return m_board[i];
}

const int LoadManager::get_focus() {
	return m_focus;
}

const int LoadManager::get_promotionMenu() {
	return m_promotionMenu;
}