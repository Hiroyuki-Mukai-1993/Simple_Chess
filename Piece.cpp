#include "Piece.h"

Piece::Piece() {
	m_type = 0;
	m_firstMoveFlag = true;
	m_pawnDoubleMoveFlag = false;
}

void Piece::set_type(piece_type type) {
	m_type |= type;
}

void Piece::set_fMoveFlag(bool flag) {
	m_firstMoveFlag = flag;
}

void Piece::set_pDoubleMoveFlag(bool flag) {
	m_pawnDoubleMoveFlag = flag;
}

void Piece::reset_type() {
	m_type = 0;
}

pieceType Piece::get_type() {
	return m_type;
}

bool Piece::get_fMoveFlag() {
	return m_firstMoveFlag;
}

bool Piece::get_pDoubleMoveFlag() {
	return m_pawnDoubleMoveFlag;
}

bool Piece::isWhite() {
	return (m_type & WHITE)?true:false;
}

bool Piece::isBlack() {
	return (m_type & BLACK)?true:false;
}