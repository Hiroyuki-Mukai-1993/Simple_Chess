#include "Game.h"

Game::Game() {
	m_focusX = -1, m_focusY = -1;
	m_memX = -1, m_memY = -1;

	m_inputMem = 0;
	m_movePieceFlag = false;

	m_turn = TURN_WHITE;

	m_signal = SIGNAL_NONE;

	m_signal = GAME_PROCEEDING;
}

game_signal Game::Proceed(InputManager* input,Board *board) {
	//テスト用
	if (m_turn == TURN_WHITE)	DrawString(0, 360, "TURN\nWHITE", GetColor(255, 255, 255));
	else if (m_turn == TURN_BLACK)	DrawString(0, 360, "TURN\nBLACK", GetColor(255, 255, 255));

	//チェックメイト・ステイルメイトの判定
	if (isCheckmate(board))		m_signal = CHECKMATE;
	else if (isStalemate(board))	m_signal = STALEMATE;

	move_piece(input,board);

	return m_signal;
}

bool Game::isCheckmate(Board* board) {

	//キングが取られたら試合終了
	int kingCnt = 0;

	for (int i = 0; i < RANK_NUM; i++) {
		for (int j = 0; j < FILE_NUM; j++) {
			if (board->get_piece(i, j)->get_type() & KING)	kingCnt++;
		}
	}

	if (kingCnt == 1)	return true;
	else				return false;
}

bool Game::isStalemate(Board* board) {
	return false;
}

//合法手か調べる
bool Game::check_legal_move(int fx,int fy,int mx,int my,Board *board,Piece *piece) {
	
	if (!(check_move1(fx, fy, mx, my, board, piece)))	return false;
	else if (!(check_move2(fx, fy, mx, my, board, piece)))	return false;
	else if (!(check_move3(fx, fy, mx, my, board, piece)))	return false;
	else if (!(check_move4(fx, fy, mx, my, board, piece)))	return false;

	if (piece->get_type() & KING) {
		if (!check_moveKing(fx, fy, mx, my, board, piece))		return false;
	}
	else if (piece->get_type() & QUEEN) {
		if (!check_moveQueen(fx, fy, mx, my, board, piece))		return false;
	}
	else if (piece->get_type() & ROOK) {
		if (!check_moveRook(fx, fy, mx, my, board, piece))		return false;
	}
	else if (piece->get_type() & BISHIOP) {
		if (!check_moveBishiop(fx, fy, mx, my, board, piece))	return false;
	}
	else if (piece->get_type() & KNIGHT) {
		if (!check_moveKnight(fx, fy, mx, my, board, piece))	return false;
	}
	else if (piece->get_type() & PAWN) {
		if (!check_movePawn(fx, fy, mx, my, board, piece))		return false;
	}

	//全条件を満たしていれば動ける
	return true;
}

//合法手チェック1
bool Game::check_move1(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	//記憶した座標が空白でなく
	if (board->get_piece(my, mx)->get_type() &&
		//記憶した座標、移動先共に盤の上なら
		0 <= fx && fx < FILE_NUM && 0 <= fy && fy < RANK_NUM && 0 <= fx && fx < FILE_NUM && 0 <= fy && fy < RANK_NUM) {
		return true;
	}
	else { return false; }
}

//合法手チェック2
bool Game::check_move2(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	//手番の駒なら動ける
	if ((m_turn == TURN_WHITE && piece->isWhite()) || (m_turn == TURN_BLACK && piece->isBlack()))	return true;
	else return false;
}

//合法手チェック3
bool Game::check_move3(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	//移動先に味方の駒がいなければ動ける
	Piece* focus_piece = board->get_piece(fy, fx);
	if (focus_piece->get_type()) {
		if ((focus_piece->isWhite() && m_turn == TURN_WHITE) || (focus_piece->isBlack() && m_turn == TURN_BLACK))	return false;
	}

	return true;
}

//合法手チェック4
bool Game::check_move4(int fx, int fy, int mx, int my, Board* board, Piece* piece) {
	//元の場所に移動は禁止
	if (fx == mx && fy == my)	return false;
	else return true;
}

//合法手チェックキング
bool Game::check_moveKing(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	if (castling(fx, fy, mx, my, board, piece))	return true;

	else {
		if (fx < mx - 1 || mx + 1 < fx || fy < my - 1 || my + 1 < fy)	return false;
		else return true;
	}
}

//合法手チェッククイーン
bool Game::check_moveQueen(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	if (check_moveRook(fx, fy, mx, my, board, piece) || check_moveBishiop(fx, fy, mx, my, board, piece))	return true;
	else return false;
}

//合法手チェックルーク
bool Game::check_moveRook(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	int file = fx - mx, rank = fy - my;

	//右移動
	if (!rank && file > 0) {
		for (int i = mx + 1; i < fx; i++) {
			if (board->get_piece(my, i)->get_type())	return false;
		}
		return true;
	}
	//左移動
	else if (!rank && file < 0) {
		for (int i = mx - 1; i > fx; i--) {
			if (board->get_piece(my, i)->get_type())	return false;
		}
		return true;
	}
	//上移動
	else if (!file && rank < 0) {
		for (int i = my - 1; i > fy; i--) {
			if (board->get_piece(i, mx)->get_type())	return false;
		}
		return true;
	}
	//下移動
	else if (!file && rank > 0) {
		for (int i = my + 1; i < fy; i++) {
			if (board->get_piece(i, mx)->get_type())	return false;
		}
		return true;
	}
	else return false;
}

//合法手チェックビショップ
bool Game::check_moveBishiop(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	int file = fx - mx, rank = fy - my;
	
	//縦横の移動量の絶対値が同じでなければ動けない
	if (abs(file) != abs(rank))	return false;

	//左上移動
	if (file < 0 && rank < 0) {
		for (int i = my - 1, j = mx - 1; i > fy; i--, j--) {
			if (board->get_piece(i, j)->get_type())	return false;
		}
		return true;
	}
	//右上移動
	else if (file > 0 && rank < 0) {
		for (int i = my - 1, j = mx + 1; i > fy; i--, j++) {
			if (board->get_piece(i, j)->get_type())	return false;
		}
		return true;
	}
	//右下移動
	else if (file > 0 && rank > 0) {
		for (int i = my + 1, j = mx + 1; i < fy; i++, j++) {
			if (board->get_piece(i, j)->get_type())	return false;
		}
		return true;
	}
	//左下移動
	else if (file < 0 && rank > 0) {
		for (int i = my + 1, j = mx - 1; i < fy; i++, j--) {
			if (board->get_piece(i, j)->get_type())	return false;
		}
		return true;
	}
	else return false;
}

//合法手チェックナイト
bool Game::check_moveKnight(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	if ((fx == mx - 1 && fy == my - 2) || (fx == mx + 1 && fy == my - 2) || (fx == mx - 1 && fy == my + 2) || (fx == mx + 1 && fy == my + 2) ||
		(fx == mx - 2 && fy == my - 1) || (fx == mx - 2 && fy == my + 1) || (fx == mx + 2 && fy == my - 1) || (fx == mx + 2 && fy == my + 1))	return true;

	else return false;
}

//合法手チェックポーン
bool Game::check_movePawn(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	if (en_passant(fx, fy, mx, my, board, piece))	return true;

	else {
		int dir;
		if (piece->isWhite())		dir = -1;
		else if (piece->isBlack())	dir = 1;

		if (fx == mx && fy == my + dir && !(board->get_piece(fy, fx)->get_type()))	return true;
		else if (fx == mx && fy == my + dir * 2 && !(board->get_piece(fy, fx)->get_type()) && piece->get_fMoveFlag()) {
			board->get_piece(fy, fx)->set_pDoubleMoveFlag(true);
			return true;
		}
		else if ((fx == mx - 1 || fx == mx + 1) && fy == my + dir && board->get_piece(fy, fx)->get_type())	return true;
		else return false;
	}
}

//キャッスリング
bool Game::castling(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	//キングが動いていたら失敗
	if (!piece->get_fMoveFlag())	return false;

	//同じ段
	if (!(fy == my))return false;

	else {
		int rook_distance, rook_distance2;

		//キングサイドキャッスリング
		if (fx == mx + 2) {
			rook_distance = 1;
			rook_distance2 = 3;

			//間に駒が置かれていないか
			for (int i = mx + 1; i < mx+rook_distance2; i++) {
				if (board->get_piece(my, i)->get_type())	return false;
			}

			//敵の駒が直射していないか
			for (int i = mx; i <= mx + rook_distance2; i++) {
				for (int y = 0; y < RANK_NUM; y++) {
					for (int x = 0; x < FILE_NUM; x++) {
						if (m_turn == TURN_WHITE) {
							if (board->get_piece(y, x)->isBlack()) {
								if (check_legal_move(i, my, x, y, board, board->get_piece(y, x)))	return false;
							}
						}
						if (m_turn == TURN_BLACK) {
							if (board->get_piece(y, x)->isWhite()) {
								if (check_legal_move(i, my, x, y, board, board->get_piece(y, x)))	return false;
							}
						}
					}
				}
			}

		}
		//クイーンサイドキャッスリング
		else if (fx == mx - 2) {
			rook_distance = -1;
			rook_distance2 = -4;

			//間に駒が置かれていないか
			for (int i = mx - 1; i > mx+rook_distance2; i--) {
				if (board->get_piece(my, i)->get_type())	return false;
			}

			//敵の駒が直射していないか
			for (int i = mx; i >= mx + rook_distance2; i--) {
				for (int y = 0; y < RANK_NUM; y++) {
					for (int x = 0; x < FILE_NUM; x++) {
						if (m_turn == TURN_WHITE) {
							if (board->get_piece(y, x)->isBlack()) {
								if (check_legal_move(i, my, x, y, board, board->get_piece(y, x)))	return false;
							}
						}
						if (m_turn == TURN_BLACK) {
							if (board->get_piece(y, x)->isWhite()) {
								if (check_legal_move(i, my, x, y, board, board->get_piece(y, x)))	return false;
							}
						}
					}
				}
			}

		}
		else return false;

		//ルークが動いていたら失敗
		if (!board->get_piece(my, mx + rook_distance2)->get_fMoveFlag())	return false;

		//ルークを動かす
		Piece* rook1 = board->get_piece(my, mx+rook_distance);
		Piece* rook2 = board->get_piece(my, mx + rook_distance2);
		rook1->reset_type();
		if (my == 7)		rook1->set_type(WHITE);
		else if (my == 0)	rook1->set_type(BLACK);
		rook1->set_type(ROOK);
		rook1->set_fMoveFlag(false);
		rook2->reset_type();
		rook2->set_fMoveFlag(false);
		return true;
	}
}

//アンパッサン
bool Game::en_passant(int fx, int fy, int mx, int my, Board* board, Piece* piece) {
	
	int dir,rank;
	
	if (piece->isWhite())	rank = 3;
	else if (piece->isBlack()) rank = 4;

	//斜め横のマスにのみアンパッサンできる
	if (fx == mx - 1)	dir = -1;
	else if (fx == mx + 1)	dir = 1;
	else return false;

	if (my != rank)	return false;

	if (board->get_lastMovedPiece() == board->get_piece(my, mx + dir)) {
		if (board->get_lastMovedPiece()->get_pDoubleMoveFlag()) {
			board->get_lastMovedPiece()->reset_type();
			return true;
		}
		else return false;
	}
	else return false;
	
}

//プロモーション
void Game::promotion(InputManager* input,Piece* piece) {
	
	//マウスの座標を取得
	int selectX = (input->get_mouseX() - PROMOTION_MENU_EDGE_X) / PROMOTION_MENU_SPACE_X;
	int selectY = (input->get_mouseY() - PROMOTION_MENU_EDGE_Y) / PROMOTION_MENU_SPACE_Y;

	//座標がメニュー内なら
	if (selectX == 0) {
		if (0 <= selectY && selectY < PROMOTION_OPTION_NUM) {
			//手番を更新
			if (m_turn == TURN_WHITE)		m_turn = TURN_BLACK;
			else if (m_turn == TURN_BLACK)	m_turn = TURN_WHITE;

			piece_type type;
			if (m_turn == TURN_WHITE)		type = WHITE;
			else if (m_turn == TURN_BLACK)	type = BLACK;

			piece->reset_type();
			piece->set_type(type);
			piece->set_fMoveFlag(false);

			switch (selectY) {
			case 0:	piece->set_type(QUEEN);		break;
			case 1:	piece->set_type(ROOK);		break;
			case 2:	piece->set_type(BISHIOP);	break;
			case 3:	piece->set_type(KNIGHT);	break;
			}

			//手番を更新
			if (m_turn == TURN_WHITE)		m_turn = TURN_BLACK;
			else if (m_turn == TURN_BLACK)	m_turn = TURN_WHITE;

			m_signal = GAME_PROCEEDING;
		}
	}
}

void Game::move_piece(InputManager* input, Board* board) {
	
	//マウスが押されていれば、座標を取得
	m_focusX = -1, m_focusY = -1;
	if (input->get_mouseX() >= BOARD_EDGE_X)	m_focusX = (input->get_mouseX() - BOARD_EDGE_X) / BOARD_SPACE_X;
	if (input->get_mouseY() >= BOARD_EDGE_Y)	m_focusY = (input->get_mouseY() - BOARD_EDGE_Y) / BOARD_SPACE_Y;

	//マウスが押された瞬間、座標を記憶
	if (!(input->get_mouseInputLogType())) {
		if (m_movePieceFlag == false) {
			m_movePieceFlag = true;
			m_memX = m_focusX, m_memY = m_focusY;
		}
	}

	//マウスが離された瞬間なら
	else if (input->get_mouseInputLogType()) {
		if (m_movePieceFlag == true) {
			m_movePieceFlag = false;

			//ゲームが通常進行中は
			if (m_signal == GAME_PROCEEDING) {
				//盤の範囲内なら
				if ((0 <= m_memX && m_memX < FILE_NUM && 0 <= m_memY && m_memY < RANK_NUM) &&
					(0 <= m_focusX && m_focusX < FILE_NUM && 0 <= m_focusY && m_focusY < RANK_NUM)) {
					//合法手なら
					if (check_legal_move(m_focusX, m_focusY, m_memX, m_memY, board, board->get_piece(m_memY, m_memX))) {

						//記憶した座標(移動元)と移動先の駒を取得
						Piece* focus_piece = board->get_piece(m_focusY, m_focusX);
						Piece* mem_piece = board->get_piece(m_memY, m_memX);

						//移動先を消去して
						focus_piece->reset_type();

						//移動先に移動元を写す
						if (mem_piece->get_type() & WHITE)		focus_piece->set_type(WHITE);
						if (mem_piece->get_type() & BLACK)		focus_piece->set_type(BLACK);
						if (mem_piece->get_type() & KING)		focus_piece->set_type(KING);
						if (mem_piece->get_type() & QUEEN)		focus_piece->set_type(QUEEN);
						if (mem_piece->get_type() & ROOK)		focus_piece->set_type(ROOK);
						if (mem_piece->get_type() & BISHIOP)	focus_piece->set_type(BISHIOP);
						if (mem_piece->get_type() & KNIGHT)		focus_piece->set_type(KNIGHT);
						if (mem_piece->get_type() & PAWN)		focus_piece->set_type(PAWN);

						//初回移動フラグを折る
						focus_piece->set_fMoveFlag(false);
						//最後に動いた駒を更新
						board->set_lastMovedPiece(focus_piece);
						//最後に動いた駒以外の、ポーン２マス移動フラグを折る
						for (int i = 0; i < RANK_NUM; i++) {
							for (int j = 0; j < FILE_NUM; j++) {
								if (board->get_piece(i, j) != board->get_lastMovedPiece()) {
									board->get_piece(i, j)->set_pDoubleMoveFlag(false);
								}
							}
						}
						//移動元を消去
						mem_piece->reset_type();

						//最後に動いた駒がポーンで、敵陣の一番奥についたら、プロモーション
						if (board->get_lastMovedPiece()->get_type() & PAWN) {

							int promotion_rank;
							if (m_turn == TURN_WHITE)		promotion_rank = 0;
							else if (m_turn == TURN_BLACK)	promotion_rank = 7;

							for (int i = 0; i < FILE_NUM; i++) {
								if (board->get_lastMovedPiece() == board->get_piece(promotion_rank, i))	m_signal = PROMOTION;
							}
						}

						//手番を更新
						if (m_turn == TURN_WHITE)		m_turn = TURN_BLACK;
						else if (m_turn == TURN_BLACK)	m_turn = TURN_WHITE;
					}
				}
			}

			else if (m_signal == PROMOTION) {
				promotion(input,board->get_lastMovedPiece());
			}

			//座標記憶を消去
			m_memX = -1, m_memY = -1;
		}
	}

	//テスト用
	//DrawFormatString(0, 100, GetColor(255, 255, 255), "m_focusX=%d\nm_focusY=%d\nm_memX=%d\nm_memY=%d", m_focusX, m_focusY, m_memX, m_memY);
}

game_turn Game::get_turn() {
	return m_turn;
}