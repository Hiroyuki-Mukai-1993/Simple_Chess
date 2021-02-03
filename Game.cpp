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
	//�e�X�g�p
	if (m_turn == TURN_WHITE)	DrawString(0, 360, "TURN\nWHITE", GetColor(255, 255, 255));
	else if (m_turn == TURN_BLACK)	DrawString(0, 360, "TURN\nBLACK", GetColor(255, 255, 255));

	//�`�F�b�N���C�g�E�X�e�C�����C�g�̔���
	if (isCheckmate(board))		m_signal = CHECKMATE;
	else if (isStalemate(board))	m_signal = STALEMATE;

	move_piece(input,board);

	return m_signal;
}

bool Game::isCheckmate(Board* board) {

	//�L���O�����ꂽ�玎���I��
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

//���@�肩���ׂ�
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

	//�S�����𖞂����Ă���Γ�����
	return true;
}

//���@��`�F�b�N1
bool Game::check_move1(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	//�L���������W���󔒂łȂ�
	if (board->get_piece(my, mx)->get_type() &&
		//�L���������W�A�ړ��拤�ɔՂ̏�Ȃ�
		0 <= fx && fx < FILE_NUM && 0 <= fy && fy < RANK_NUM && 0 <= fx && fx < FILE_NUM && 0 <= fy && fy < RANK_NUM) {
		return true;
	}
	else { return false; }
}

//���@��`�F�b�N2
bool Game::check_move2(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	//��Ԃ̋�Ȃ瓮����
	if ((m_turn == TURN_WHITE && piece->isWhite()) || (m_turn == TURN_BLACK && piece->isBlack()))	return true;
	else return false;
}

//���@��`�F�b�N3
bool Game::check_move3(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	//�ړ���ɖ����̋���Ȃ���Γ�����
	Piece* focus_piece = board->get_piece(fy, fx);
	if (focus_piece->get_type()) {
		if ((focus_piece->isWhite() && m_turn == TURN_WHITE) || (focus_piece->isBlack() && m_turn == TURN_BLACK))	return false;
	}

	return true;
}

//���@��`�F�b�N4
bool Game::check_move4(int fx, int fy, int mx, int my, Board* board, Piece* piece) {
	//���̏ꏊ�Ɉړ��͋֎~
	if (fx == mx && fy == my)	return false;
	else return true;
}

//���@��`�F�b�N�L���O
bool Game::check_moveKing(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	if (castling(fx, fy, mx, my, board, piece))	return true;

	else {
		if (fx < mx - 1 || mx + 1 < fx || fy < my - 1 || my + 1 < fy)	return false;
		else return true;
	}
}

//���@��`�F�b�N�N�C�[��
bool Game::check_moveQueen(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	if (check_moveRook(fx, fy, mx, my, board, piece) || check_moveBishiop(fx, fy, mx, my, board, piece))	return true;
	else return false;
}

//���@��`�F�b�N���[�N
bool Game::check_moveRook(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	int file = fx - mx, rank = fy - my;

	//�E�ړ�
	if (!rank && file > 0) {
		for (int i = mx + 1; i < fx; i++) {
			if (board->get_piece(my, i)->get_type())	return false;
		}
		return true;
	}
	//���ړ�
	else if (!rank && file < 0) {
		for (int i = mx - 1; i > fx; i--) {
			if (board->get_piece(my, i)->get_type())	return false;
		}
		return true;
	}
	//��ړ�
	else if (!file && rank < 0) {
		for (int i = my - 1; i > fy; i--) {
			if (board->get_piece(i, mx)->get_type())	return false;
		}
		return true;
	}
	//���ړ�
	else if (!file && rank > 0) {
		for (int i = my + 1; i < fy; i++) {
			if (board->get_piece(i, mx)->get_type())	return false;
		}
		return true;
	}
	else return false;
}

//���@��`�F�b�N�r�V���b�v
bool Game::check_moveBishiop(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	int file = fx - mx, rank = fy - my;
	
	//�c���̈ړ��ʂ̐�Βl�������łȂ���Γ����Ȃ�
	if (abs(file) != abs(rank))	return false;

	//����ړ�
	if (file < 0 && rank < 0) {
		for (int i = my - 1, j = mx - 1; i > fy; i--, j--) {
			if (board->get_piece(i, j)->get_type())	return false;
		}
		return true;
	}
	//�E��ړ�
	else if (file > 0 && rank < 0) {
		for (int i = my - 1, j = mx + 1; i > fy; i--, j++) {
			if (board->get_piece(i, j)->get_type())	return false;
		}
		return true;
	}
	//�E���ړ�
	else if (file > 0 && rank > 0) {
		for (int i = my + 1, j = mx + 1; i < fy; i++, j++) {
			if (board->get_piece(i, j)->get_type())	return false;
		}
		return true;
	}
	//�����ړ�
	else if (file < 0 && rank > 0) {
		for (int i = my + 1, j = mx - 1; i < fy; i++, j--) {
			if (board->get_piece(i, j)->get_type())	return false;
		}
		return true;
	}
	else return false;
}

//���@��`�F�b�N�i�C�g
bool Game::check_moveKnight(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	if ((fx == mx - 1 && fy == my - 2) || (fx == mx + 1 && fy == my - 2) || (fx == mx - 1 && fy == my + 2) || (fx == mx + 1 && fy == my + 2) ||
		(fx == mx - 2 && fy == my - 1) || (fx == mx - 2 && fy == my + 1) || (fx == mx + 2 && fy == my - 1) || (fx == mx + 2 && fy == my + 1))	return true;

	else return false;
}

//���@��`�F�b�N�|�[��
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

//�L���b�X�����O
bool Game::castling(int fx, int fy, int mx, int my, Board* board, Piece* piece) {

	//�L���O�������Ă����玸�s
	if (!piece->get_fMoveFlag())	return false;

	//�����i
	if (!(fy == my))return false;

	else {
		int rook_distance, rook_distance2;

		//�L���O�T�C�h�L���b�X�����O
		if (fx == mx + 2) {
			rook_distance = 1;
			rook_distance2 = 3;

			//�Ԃɋ�u����Ă��Ȃ���
			for (int i = mx + 1; i < mx+rook_distance2; i++) {
				if (board->get_piece(my, i)->get_type())	return false;
			}

			//�G�̋���˂��Ă��Ȃ���
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
		//�N�C�[���T�C�h�L���b�X�����O
		else if (fx == mx - 2) {
			rook_distance = -1;
			rook_distance2 = -4;

			//�Ԃɋ�u����Ă��Ȃ���
			for (int i = mx - 1; i > mx+rook_distance2; i--) {
				if (board->get_piece(my, i)->get_type())	return false;
			}

			//�G�̋���˂��Ă��Ȃ���
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

		//���[�N�������Ă����玸�s
		if (!board->get_piece(my, mx + rook_distance2)->get_fMoveFlag())	return false;

		//���[�N�𓮂���
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

//�A���p�b�T��
bool Game::en_passant(int fx, int fy, int mx, int my, Board* board, Piece* piece) {
	
	int dir,rank;
	
	if (piece->isWhite())	rank = 3;
	else if (piece->isBlack()) rank = 4;

	//�΂߉��̃}�X�ɂ̂݃A���p�b�T���ł���
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

//�v�����[�V����
void Game::promotion(InputManager* input,Piece* piece) {
	
	//�}�E�X�̍��W���擾
	int selectX = (input->get_mouseX() - PROMOTION_MENU_EDGE_X) / PROMOTION_MENU_SPACE_X;
	int selectY = (input->get_mouseY() - PROMOTION_MENU_EDGE_Y) / PROMOTION_MENU_SPACE_Y;

	//���W�����j���[���Ȃ�
	if (selectX == 0) {
		if (0 <= selectY && selectY < PROMOTION_OPTION_NUM) {
			//��Ԃ��X�V
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

			//��Ԃ��X�V
			if (m_turn == TURN_WHITE)		m_turn = TURN_BLACK;
			else if (m_turn == TURN_BLACK)	m_turn = TURN_WHITE;

			m_signal = GAME_PROCEEDING;
		}
	}
}

void Game::move_piece(InputManager* input, Board* board) {
	
	//�}�E�X��������Ă���΁A���W���擾
	m_focusX = -1, m_focusY = -1;
	if (input->get_mouseX() >= BOARD_EDGE_X)	m_focusX = (input->get_mouseX() - BOARD_EDGE_X) / BOARD_SPACE_X;
	if (input->get_mouseY() >= BOARD_EDGE_Y)	m_focusY = (input->get_mouseY() - BOARD_EDGE_Y) / BOARD_SPACE_Y;

	//�}�E�X�������ꂽ�u�ԁA���W���L��
	if (!(input->get_mouseInputLogType())) {
		if (m_movePieceFlag == false) {
			m_movePieceFlag = true;
			m_memX = m_focusX, m_memY = m_focusY;
		}
	}

	//�}�E�X�������ꂽ�u�ԂȂ�
	else if (input->get_mouseInputLogType()) {
		if (m_movePieceFlag == true) {
			m_movePieceFlag = false;

			//�Q�[�����ʏ�i�s����
			if (m_signal == GAME_PROCEEDING) {
				//�Ղ͈͓̔��Ȃ�
				if ((0 <= m_memX && m_memX < FILE_NUM && 0 <= m_memY && m_memY < RANK_NUM) &&
					(0 <= m_focusX && m_focusX < FILE_NUM && 0 <= m_focusY && m_focusY < RANK_NUM)) {
					//���@��Ȃ�
					if (check_legal_move(m_focusX, m_focusY, m_memX, m_memY, board, board->get_piece(m_memY, m_memX))) {

						//�L���������W(�ړ���)�ƈړ���̋���擾
						Piece* focus_piece = board->get_piece(m_focusY, m_focusX);
						Piece* mem_piece = board->get_piece(m_memY, m_memX);

						//�ړ������������
						focus_piece->reset_type();

						//�ړ���Ɉړ������ʂ�
						if (mem_piece->get_type() & WHITE)		focus_piece->set_type(WHITE);
						if (mem_piece->get_type() & BLACK)		focus_piece->set_type(BLACK);
						if (mem_piece->get_type() & KING)		focus_piece->set_type(KING);
						if (mem_piece->get_type() & QUEEN)		focus_piece->set_type(QUEEN);
						if (mem_piece->get_type() & ROOK)		focus_piece->set_type(ROOK);
						if (mem_piece->get_type() & BISHIOP)	focus_piece->set_type(BISHIOP);
						if (mem_piece->get_type() & KNIGHT)		focus_piece->set_type(KNIGHT);
						if (mem_piece->get_type() & PAWN)		focus_piece->set_type(PAWN);

						//����ړ��t���O��܂�
						focus_piece->set_fMoveFlag(false);
						//�Ō�ɓ���������X�V
						board->set_lastMovedPiece(focus_piece);
						//�Ō�ɓ�������ȊO�́A�|�[���Q�}�X�ړ��t���O��܂�
						for (int i = 0; i < RANK_NUM; i++) {
							for (int j = 0; j < FILE_NUM; j++) {
								if (board->get_piece(i, j) != board->get_lastMovedPiece()) {
									board->get_piece(i, j)->set_pDoubleMoveFlag(false);
								}
							}
						}
						//�ړ���������
						mem_piece->reset_type();

						//�Ō�ɓ�������|�[���ŁA�G�w�̈�ԉ��ɂ�����A�v�����[�V����
						if (board->get_lastMovedPiece()->get_type() & PAWN) {

							int promotion_rank;
							if (m_turn == TURN_WHITE)		promotion_rank = 0;
							else if (m_turn == TURN_BLACK)	promotion_rank = 7;

							for (int i = 0; i < FILE_NUM; i++) {
								if (board->get_lastMovedPiece() == board->get_piece(promotion_rank, i))	m_signal = PROMOTION;
							}
						}

						//��Ԃ��X�V
						if (m_turn == TURN_WHITE)		m_turn = TURN_BLACK;
						else if (m_turn == TURN_BLACK)	m_turn = TURN_WHITE;
					}
				}
			}

			else if (m_signal == PROMOTION) {
				promotion(input,board->get_lastMovedPiece());
			}

			//���W�L��������
			m_memX = -1, m_memY = -1;
		}
	}

	//�e�X�g�p
	//DrawFormatString(0, 100, GetColor(255, 255, 255), "m_focusX=%d\nm_focusY=%d\nm_memX=%d\nm_memY=%d", m_focusX, m_focusY, m_memX, m_memY);
}

game_turn Game::get_turn() {
	return m_turn;
}