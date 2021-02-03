#pragma once

#include <vector>

class AI
{
private:
	// фигура за которую играет AI
	bool m_markAI;
	// проверяет, если ли строка с n-1 одинаковыми символами и 1 пустым
	// ее нужно занять, чтобы либо выиграть, либо не дать выиграть оппоненту
	int checkLines();
	// делает ход крестиками
	void _AIMovesCrosses(std::vector<int> &moves, int &row, int &col);
	// делает ход ноликами
	void _AIMovesNoughts(std::vector<int> &moves, int &row, int &col);
public:
	// в параметры - фигура, за которую играет AI
	AI(bool markAI) : m_markAI{ markAI } {}
	~AI() {}

	bool getAIMark() const { return m_markAI; }

	// AI делает ход + возвращает координаты, куда поставил фигуру
	void _AI_makes_move(int &row, int &col);
};