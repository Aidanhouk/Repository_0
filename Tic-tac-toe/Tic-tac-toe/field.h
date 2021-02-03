#pragma once

#include <vector>

class Field
{
private:
	// само поле
	int **m_field;
	// сколько осталось пустых ячеек
	int m_blanks;
	// нужны, чтобы перечеркнуть выигрышную линию
	int m_rowOrCol, m_finishLineDirection;
	// какая фигура сейчас ставится (1 - крестики, 2 - нолики)
	bool m_turn{ 1 };
	// сюда будут записываться все ходы, нужно для работы AI
	std::vector<int> m_moves;
public:
	Field();
	~Field();

	// проверяет, есть ли линия, заполненная 1 типом фигур
	int finishedLineCheck();
	// уменьшить кол-во пустых ячеек (если сделан ход)
	void decreaseBlanks() { --m_blanks; }
	// проверка на ничью
	bool isDraw() { return !m_blanks; }
	// ход сменился, значит ставится должная другая фигура
	void changeTurn() { m_turn = !m_turn; }

	std::vector<int> &getMovesVector() { return m_moves; }
	void setMovesVector(std::vector<int> &vc) { m_moves = vc; }
	bool getTurn() const { return m_turn; }
	int getRowOrCol() const { return m_rowOrCol; }
	int getFinishLineDirection() const { return m_finishLineDirection; }

	int* operator[](const int index) { return m_field[index]; }
};