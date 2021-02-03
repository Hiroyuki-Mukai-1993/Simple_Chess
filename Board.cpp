#include "Board.h"

Board::Board() {
	for (int i = 0; i < RANK_NUM; i++) {
		for (int j = 0; j < FILE_NUM; j++) {
			m_piece[i][j] = new Piece;
		}
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < FILE_NUM; j++) {
			m_piece[i][j]->set_type(BLACK);
		}
	}
	for (int i = 6; i < 8; i++) {
		for (int j = 0; j < FILE_NUM; j++) {
			m_piece[i][j]->set_type(WHITE);
		}
	}

	m_piece[0][4]->set_type(KING);
	m_piece[7][4]->set_type(KING);
	m_piece[0][3]->set_type(QUEEN);
	m_piece[7][3]->set_type(QUEEN);
	m_piece[0][0]->set_type(ROOK);
	m_piece[0][7]->set_type(ROOK);
	m_piece[7][0]->set_type(ROOK);
	m_piece[7][7]->set_type(ROOK);
	m_piece[0][2]->set_type(BISHIOP);
	m_piece[0][5]->set_type(BISHIOP);
	m_piece[7][2]->set_type(BISHIOP);
	m_piece[7][5]->set_type(BISHIOP);
	m_piece[0][1]->set_type(KNIGHT);
	m_piece[0][6]->set_type(KNIGHT);
	m_piece[7][1]->set_type(KNIGHT);
	m_piece[7][6]->set_type(KNIGHT);

	for (int i = 0; i < FILE_NUM; i++) {
		m_piece[1][i]->set_type(PAWN);
		m_piece[6][i]->set_type(PAWN);
	}

	m_lastMovedPiece = 0;
}

Board::~Board() {
	for (int i = 0; i < RANK_NUM; i++) {
		for (int j = 0; j < FILE_NUM; j++) {
			delete m_piece[i][j];
		}
	}
}

Piece* Board::get_piece(int y, int x) {
	return m_piece[y][x];
}

void Board::set_lastMovedPiece(Piece* piece) {
	m_lastMovedPiece = piece;
}

Piece* Board::get_lastMovedPiece() {
	return m_lastMovedPiece;
}