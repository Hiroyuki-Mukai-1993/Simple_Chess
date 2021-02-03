#pragma once

#include"Piece.h"

#define RANK_NUM 8
#define FILE_NUM 8

#define BOARD_EDGE_X 80
#define BOARD_EDGE_Y 0
#define BOARD_SPACE_X 60
#define BOARD_SPACE_Y 60

#define PROMOTION_MENU_EDGE_X 0
#define PROMOTION_MENU_EDGE_Y 0
#define PROMOTION_MENU_SPACE_X 80
#define PROMOTION_MENU_SPACE_Y 80
#define PROMOTION_MENU_NUM 4

class Board
{
private:
	Piece *m_piece[RANK_NUM][FILE_NUM];
	Piece *m_lastMovedPiece;				//ç≈å„Ç…ìÆÇ¢ÇΩãÓ
public:
	Board();
	~Board();

	Piece* get_piece(int, int);
	void set_lastMovedPiece(Piece*);
	Piece* get_lastMovedPiece();
};

