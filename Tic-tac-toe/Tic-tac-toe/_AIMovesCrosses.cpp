#include "_AI.h"

#include "globals.h"
#include "field.h"

void AI::_AIMovesCrosses(std::vector<int> &moves, int &row, int &col)
{
	// чтобы завершить линию / не дать завершить оппоненту
	int q{ -1 };
	switch (moves.size())
	{
		// 2 ход
	case 2:
		int x;
		switch (moves[1])
		{
		case 1:
		case 2:
		case 5:
			// 6
			moves.push_back(6);
			row = 6 / n;
			col = 6 % n;
			break;
		case 3:
		case 6:
		case 7:
			// 2
			moves.push_back(2);
			row = 2 / n;
			col = 2 % n;
			break;
		case 8:
			// 2 или 6
			x = rand() % 2;
			x = x ? 2 : 6;
			moves.push_back(x);
			row = x / n;
			col = x % n;
			break;
		case 4:
			// 8
			moves.push_back(8);
			row = 8 / n;
			col = 8 % n;
			break;
		}
		break;
		// 3 ход
	case 4:
		q = checkLines();
		if (q != -1) {
			moves.push_back(q);
			row = q / n;
			col = q % n;
			break;
		}
		switch (moves[1])
		{
		case 1:
		case 2:
		case 5:
		case 3:
		case 6:
		case 7:
			// тогда moves[3] = 1 или 3, не важно
			// 8
			moves.push_back(8);
			row = 8 / n;
			col = 8 % n;
			break;
		case 4:
			switch (moves[3])
			{
			case 2:
				// 6
				moves.push_back(6);
				row = 6 / n;
				col = 6 % n;
				break;
			case 6:
				// 2
				moves.push_back(2);
				row = 2 / n;
				col = 2 % n;
				break;
			}
			break;
		case 8:
			switch (moves[3])
			{
			case 1:
				// 6
				moves.push_back(6);
				row = 6 / n;
				col = 6 % n;
				break;
			case 3:
				// 2
				moves.push_back(2);
				row = 2 / n;
				col = 2 % n;
				break;
			}
		}
		break;
		// 4 ход
	case 6:
		q = checkLines();
		if (q != -1) {
			moves.push_back(q);
			row = q / n;
			col = q % n;
			break;
		}
		switch (moves[3])
		{
		case 2:
			if (moves[4] == 6) {
				if (moves[5] == 7) {
					// 3
					moves.push_back(3);
					row = 3 / n;
					col = 3 % n;
					break;
				}
				else {
					// 7
					moves.push_back(7);
					row = 7 / n;
					col = 7 % n;
					break;
				}
			}
			break;
		case 6:
			if (moves[4] == 2) {
				if (moves[5] == 1) {
					// 5
					moves.push_back(5);
					row = 5 / n;
					col = 5 % n;
					break;
				}
				else {
					// 1
					moves.push_back(1);
					row = 1 / n;
					col = 1 % n;
					break;
				}
			}
			break;
		}
		break;
		// 5 ход
	case 8:
		// тут остается одна свободная ячейка на поле
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (!(*field)[i][j]) {
					moves.push_back(i * n + j);
					row = j;
					col = i;
					break;
				}
			}
		}
		break;
	}
}