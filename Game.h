#pragma once

#include<math.h>
#include"InputManager.h"
#include"Board.h"

#define PROMOTION_OPTION_NUM 4
#define KING_DIRECTION_NUM 9

typedef enum {
	TURN_WHITE,
	TURN_BLACK
}game_turn;

typedef enum {
	SIGNAL_NONE,
	GAME_PROCEEDING,
	PROMOTION,
	CHECKMATE,
	STALEMATE
}game_signal;

class Game
{
private:
	int m_focusX, m_focusY;
	int m_memX, m_memY;

	int m_inputMem;
	bool m_movePieceFlag;

	game_turn m_turn;			//手番
	game_signal m_signal;		//MainManagerに渡す指示
public:
	Game();

	//進行メイン
	game_signal Proceed(InputManager*,Board*);

	//チェックメイト・ステイルメイトの判定
	bool isCheckmate(Board*);
	bool isStalemate(Board*);

	//合法手か調べる
	bool check_legal_move(int,int,int,int,Board*,Piece*);
	bool check_move1(int, int, int, int, Board*, Piece*);
	bool check_move2(int, int, int, int, Board*, Piece*);
	bool check_move3(int, int, int, int, Board*, Piece*);
	bool check_move4(int, int, int, int, Board*, Piece*);

	bool check_moveKing(int, int, int, int, Board*, Piece*);
	bool check_moveQueen(int, int, int, int, Board*, Piece*);
	bool check_moveRook(int, int, int, int, Board*, Piece*);
	bool check_moveBishiop(int, int, int, int, Board*, Piece*);
	bool check_moveKnight(int, int, int, int, Board*, Piece*);
	bool check_movePawn(int, int, int, int, Board*, Piece*);

	bool castling(int, int, int, int, Board*, Piece*);
	bool en_passant(int, int, int, int, Board*, Piece*);

	//プロモーション
	void promotion(InputManager*,Piece*);
	
	//駒を動かす
	void move_piece(InputManager*, Board*);

	//手番を返す
	game_turn get_turn();

};

