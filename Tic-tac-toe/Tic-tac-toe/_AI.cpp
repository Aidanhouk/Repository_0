#include "_AI.h"

#include "globals.h"
#include "field.h"

void AI::_AI_makes_move(int & row, int & col)
{
	// получим вектор ходов
	std::vector<int> moves{ field->getMovesVector() };

	// фигура AI
	bool markAI{ !static_cast<bool>(moves.size() % 2) };
	// чтобы завершить линию / не дать завершить оппоненту
	int q{ -1 };

	// если 1-ый ход, то ставиться всегда в левый верхний угол
	if (!moves.size()) {
		moves.push_back(0);
		row = 0;
		col = 0;
	}
	else {
		// если размер поля не 3, то сначала вызывается checkLines
		q = checkLines();
		if (q != -1) {
			moves.push_back(q);
			row = q / n;
			col = q % n;
			field->setMovesVector(moves);
			return;
		}
		// если фигура не поставлена, то фулл рандом
		if (n != 3) {
			int i;
			while (1) {
				i = rand() % (n * n);
				bool f = 0;
				for (auto & var : moves) {
					if (var == i) {
						f = 1;
						break;
					}
				}
				if (!f) {
					break;
				}
			}
			moves.push_back(i);
			row = i / n;
			col = i % n;
		}
		else {
			// если AI должен ставить крестик
			if (markAI == 1) {
				_AIMovesCrosses(moves, row, col);
			}
			// если нолик
			else {
				_AIMovesNoughts(moves, row, col);
			}
		}
	}
	field->setMovesVector(moves);
}