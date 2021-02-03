#pragma once

#include<stdio.h>

typedef enum {
	KING=1<<0,
	QUEEN=1<<1,
	ROOK=1<<2,
	BISHIOP=1<<3,
	KNIGHT=1<<4,
	PAWN=1<<5,

	WHITE=1<<6,
	BLACK=1<<7
}piece_type;

typedef unsigned char pieceType;

class Piece
{
private:
	pieceType m_type;
	bool m_firstMoveFlag;
	bool m_pawnDoubleMoveFlag;
public:
	Piece();

	void set_type(piece_type);
	void set_fMoveFlag(bool);
	void set_pDoubleMoveFlag(bool);

	void reset_type();

	pieceType get_type();
	bool get_fMoveFlag();
	bool get_pDoubleMoveFlag();
	
	bool isWhite();
	bool isBlack();
};

