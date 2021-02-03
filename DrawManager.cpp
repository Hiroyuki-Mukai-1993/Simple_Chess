#include "DrawManager.h"

void DrawManager::draw_main(InputManager *input,LoadManager *load,Board *board,game_signal signal,game_turn turn) {
	SetDrawScreen(DX_SCREEN_BACK);

	draw_board(load);
	draw_piece(load, board);
	draw_focus(input, load->get_focus());

	if (signal == PROMOTION)	draw_promotion_menu(load,turn);

	if (signal == CHECKMATE || signal == STALEMATE)	draw_result(signal, turn);

	//テスト用
	//draw_test(input,board);

	ScreenFlip();
	ClearDrawScreen();
}

void DrawManager::draw_board(LoadManager* load) {
	for (int i = 0; i < RANK_NUM; i++) {
		for (int j = 0; j < FILE_NUM; j++) {
			DrawExtendGraph(BOARD_EDGE_X + j * BOARD_SPACE_X, BOARD_EDGE_Y + i * BOARD_SPACE_Y, BOARD_EDGE_X + (j + 1) * BOARD_SPACE_X, BOARD_EDGE_Y + (i + 1) * BOARD_SPACE_Y, load->get_board((i + j) % 2), true);
		}
	}
}

void DrawManager::draw_piece(LoadManager *load,Board* board) {
	for (int i = 0; i < RANK_NUM; i++) {
		for (int j = 0; j < FILE_NUM; j++) {
			int img=0;

			if (board->get_piece(i, j)->isWhite()) {
				if (board->get_piece(i, j)->get_type() & KING)	img = load->get_piece(0, 0);
				if (board->get_piece(i, j)->get_type() & QUEEN)	img = load->get_piece(0, 1);
				if (board->get_piece(i, j)->get_type() & ROOK)	img = load->get_piece(0, 2);
				if (board->get_piece(i, j)->get_type() & BISHIOP)	img = load->get_piece(0, 3);
				if (board->get_piece(i, j)->get_type() & KNIGHT)	img = load->get_piece(0, 4);
				if (board->get_piece(i, j)->get_type() & PAWN)	img = load->get_piece(0, 5);
			}
			if (board->get_piece(i, j)->isBlack()) {
				if (board->get_piece(i, j)->get_type() & KING)	img = load->get_piece(1, 0);
				if (board->get_piece(i, j)->get_type() & QUEEN)	img = load->get_piece(1, 1);
				if (board->get_piece(i, j)->get_type() & ROOK)	img = load->get_piece(1, 2);
				if (board->get_piece(i, j)->get_type() & BISHIOP)	img = load->get_piece(1, 3);
				if (board->get_piece(i, j)->get_type() & KNIGHT)	img = load->get_piece(1, 4);
				if (board->get_piece(i, j)->get_type() & PAWN)	img = load->get_piece(1, 5);
			}
			
			DrawExtendGraph(BOARD_EDGE_X + j * BOARD_SPACE_X, BOARD_EDGE_Y + i * BOARD_SPACE_Y, BOARD_EDGE_X + (j + 1) * BOARD_SPACE_X, BOARD_EDGE_Y + (i + 1) * BOARD_SPACE_Y, img, true);
		}
	}
}

void DrawManager::draw_focus(InputManager* input, int handle) {
	int x=-1, y=-1;
	if(input->get_mouseX()>=BOARD_EDGE_X)	x = (input->get_mouseX() - BOARD_EDGE_X) / BOARD_SPACE_X;
	if(input->get_mouseY()>=BOARD_EDGE_Y)	y = (input->get_mouseY() - BOARD_EDGE_Y) / BOARD_SPACE_Y;

	//テスト用
	//DrawFormatString(0, 60, GetColor(255, 255, 255), "focus: x=%d,y=%d", x, y);

	if(0<=x&&x<FILE_NUM&&0<=y&&y<RANK_NUM){
		DrawExtendGraph(BOARD_EDGE_X + x * BOARD_SPACE_X, BOARD_EDGE_Y + y * BOARD_SPACE_Y, BOARD_EDGE_X + (x + 1) * BOARD_SPACE_X, BOARD_EDGE_Y + (y + 1) * BOARD_SPACE_Y, handle, true);
	}
}

void DrawManager::draw_promotion_menu(LoadManager* load,game_turn turn) {
	int handle;
	if (turn == TURN_WHITE)			handle = 1;
	else if (turn == TURN_BLACK)	handle = 0;

	DrawExtendGraph(PROMOTION_MENU_EDGE_X, PROMOTION_MENU_EDGE_Y, PROMOTION_MENU_EDGE_X + PROMOTION_MENU_SPACE_X, PROMOTION_MENU_EDGE_Y + PROMOTION_MENU_SPACE_Y * PROMOTION_MENU_NUM,
		load->get_promotionMenu(), true);
	DrawExtendGraph(PROMOTION_MENU_EDGE_X, PROMOTION_MENU_EDGE_Y + PROMOTION_MENU_SPACE_Y * 0, PROMOTION_MENU_EDGE_X + PROMOTION_MENU_SPACE_X, PROMOTION_MENU_EDGE_Y+PROMOTION_MENU_SPACE_Y * (0 + 1),
		load->get_piece(handle, 1), true);
	DrawExtendGraph(PROMOTION_MENU_EDGE_X, PROMOTION_MENU_EDGE_Y + PROMOTION_MENU_SPACE_Y * 1, PROMOTION_MENU_EDGE_X + PROMOTION_MENU_SPACE_X, PROMOTION_MENU_EDGE_Y + PROMOTION_MENU_SPACE_Y * (1 + 1),
		load->get_piece(handle, 2), true);
	DrawExtendGraph(PROMOTION_MENU_EDGE_X, PROMOTION_MENU_EDGE_Y + PROMOTION_MENU_SPACE_Y * 2, PROMOTION_MENU_EDGE_X + PROMOTION_MENU_SPACE_X, PROMOTION_MENU_EDGE_Y + PROMOTION_MENU_SPACE_Y * (2 + 1),
		load->get_piece(handle, 3), true);
	DrawExtendGraph(PROMOTION_MENU_EDGE_X, PROMOTION_MENU_EDGE_Y + PROMOTION_MENU_SPACE_Y * 3, PROMOTION_MENU_EDGE_X + PROMOTION_MENU_SPACE_X, PROMOTION_MENU_EDGE_Y + PROMOTION_MENU_SPACE_Y * (3 + 1),
		load->get_piece(handle, 4), true);
}

void DrawManager::draw_result(game_signal signal,game_turn turn) {
	
	char winner[256]="";
	if (turn == TURN_WHITE)strcpy_s(winner, "Black");
	if (turn == TURN_BLACK)strcpy_s(winner, "White");
	
	if (signal == CHECKMATE)	DrawFormatString(0, 400, GetColor(255, 255, 255), "Checkmate! %sWins!", winner);
	else if (signal = STALEMATE)	DrawFormatString(0, 400, GetColor(255, 255, 255), "Stalemate!Game is a draw.");
}

void DrawManager::draw_test(InputManager *input,Board *board) {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "m_mouseX=%d,m_mouseY=%d\nm_mouseInputState=%d\nm_mouseInputLogType=%d\n",
		input->get_mouseX(), input->get_mouseY(), input->get_mouseInputState(), input->get_mouseInputLogType());
}