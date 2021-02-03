#include "_AI.h"

#include "globals.h"
#include "field.h"

void AI::_AIMovesNoughts(std::vector<int>& moves, int &row, int &col)
{
	// чтобы завершить линию / не дать завершить оппоненту
	int q{ -1 };
	// перменная для рандома
	int x;
	// нужно для одного из случаев
	static bool b{ 0 };
	switch (moves.size())
	{
		// 1 ход
	case 1:
		q = checkLines();
		if (q != -1) {
			moves.push_back(q);
			row = q / n;
			col = q % n;
			break;
		}
		switch (moves[0])
		{
		case 0:
		case 2:
		case 6:
		case 8:
		case 1:
		case 3:
		case 5:
		case 7:
			// если можно, всегда ставим в центр
			moves.push_back(4);
			row = 4 / n;
			col = 4 % n;
			break;
		case 4:
			// тут захардкодим левый верхний угол
			moves.push_back(0);
			row = 0 / n;
			col = 0 % n;
			break;
		}
		break;
		// 2 ход
	case 3:
		q = checkLines();
		if (q != -1) {
			moves.push_back(q);
			row = q / n;
			col = q % n;
			break;
		}
		if (moves[0] == 4) { // тогда moves[2] точно = 8
			x = rand() % 2;
			x = x ? 2 : 6;
			moves.push_back(x);
			row = x / n;
			col = x % n;
			break;
		}
		if (moves[1] == 4) {
			switch (moves[0])
			{
			case 1:
				switch (moves[2])
				{
				case 3:
					// 0
					moves.push_back(0);
					row = 0 / n;
					col = 0 % n;
					b = 1;
					break;
				case 5:
					// 2
					moves.push_back(2);
					row = 2 / n;
					col = 2 % n;
					b = 1;
					break;
				case 6:
					// 0
					moves.push_back(0);
					row = 0 / n;
					col = 0 % n;
					break;
				case 8:
					// 2
					moves.push_back(2);
					row = 2 / n;
					col = 2 % n;
					break;
				case 7:
					do {
						x = rand() % 5;
						x *= 2;
					} while (x == 4); // нужен любой угол, 4 - это центр
					moves.push_back(x);
					row = x / n;
					col = x % n;
					break;
				}
				break;
			case 3:
				switch (moves[2])
				{
				case 1:
					// 0
					moves.push_back(0);
					row = 0 / n;
					col = 0 % n;
					b = 1;
					break;
				case 7:
					// 6
					moves.push_back(6);
					row = 6 / n;
					col = 6 % n;
					b = 1;
					break;
				case 2:
					// 0
					moves.push_back(0);
					row = 0 / n;
					col = 0 % n;
					break;
				case 8:
					// 6
					moves.push_back(6);
					row = 6 / n;
					col = 6 % n;
					break;
				case 5:
					do {
						x = rand() % 5;
						x *= 2;
					} while (x == 4); // нужен любой угол, 4 - это центр
					moves.push_back(x);
					row = x / n;
					col = x % n;
					break;
				}
				break;
			case 5:
				switch (moves[2])
				{
				case 1:
					// 2
					moves.push_back(2);
					row = 2 / n;
					col = 2 % n;
					b = 1;
					break;
				case 7:
					// 8
					moves.push_back(8);
					row = 8 / n;
					col = 8 % n;
					b = 1;
					break;
				case 0:
					// 2
					moves.push_back(2);
					row = 2 / n;
					col = 2 % n;
					break;
				case 6:
					// 8
					moves.push_back(8);
					row = 8 / n;
					col = 8 % n;
					break;
				case 3:
					do {
						x = rand() % 5;
						x *= 2;
					} while (x == 4); // нужен любой угол, 4 - это центр
					moves.push_back(x);
					row = x / n;
					col = x % n;
					break;
				}
				break;
			case 7:
				switch (moves[2])
				{
				case 3:
					// 6
					moves.push_back(6);
					row = 6 / n;
					col = 6 % n;
					b = 1;
					break;
				case 5:
					// 8
					moves.push_back(8);
					row = 8 / n;
					col = 8 % n;
					b = 1;
					break;
				case 0:
					// 6
					moves.push_back(6);
					row = 6 / n;
					col = 6 % n;
					break;
				case 2:
					// 8
					moves.push_back(8);
					row = 8 / n;
					col = 8 % n;
					break;
				case 1:
					do {
						x = rand() % 5;
						x *= 2;
					} while (x == 4); // нужен любой угол, 4 - это центр
					moves.push_back(x);
					row = x / n;
					col = x % n;
					break;
				}
				break;
			case 0:
				if (moves[2] == 8) {
					x = rand() % 4;
					x = x * 2 + 1;
					moves.push_back(x);
					row = x / n;
					col = x % n;
					break;
				}
			case 2:
				if (moves[2] == 6) {
					x = rand() % 4;
					x = x * 2 + 1;
					moves.push_back(x);
					row = x / n;
					col = x % n;
					break;
				}
			case 6:
				if (moves[2] == 2) {
					x = rand() % 4;
					x = x * 2 + 1;
					moves.push_back(x);
					row = x / n;
					col = x % n;
					break;
				}
			case 8:
				if (moves[2] == 0) {
					x = rand() % 4;
					x = x * 2 + 1;
					moves.push_back(x);
					row = x / n;
					col = x % n;
					break;
				}
				switch (moves[2])
				{
				case 1:
					switch (moves[0])
					{
					case 2:
						moves.push_back(0);
						row = 0 / n;
						col = 0 % n;
						break;
					case 5:
						moves.push_back(8);
						row = 8 / n;
						col = 8 % n;
						break;
					}
					break;
				case 3:
					switch (moves[0])
					{
					case 2:
						moves.push_back(0);
						row = 0 / n;
						col = 0 % n;
						break;
					case 8:
						moves.push_back(6);
						row = 6 / n;
						col = 6 % n;
						break;
					}
					break;
				case 5:
					switch (moves[0])
					{
					case 0:
						moves.push_back(2);
						row = 2 / n;
						col = 2 % n;
						break;
					case 6:
						moves.push_back(8);
						row = 8 / n;
						col = 8 % n;
						break;
					}
					break;
				case 7:
					switch (moves[0])
					{
					case 0:
						moves.push_back(6);
						row = 6 / n;
						col = 6 % n;
						break;
					case 2:
						moves.push_back(8);
						row = 8 / n;
						col = 8 % n;
						break;
					}
					break;
				}
				break;
			}
		}
		break;
		// 3 ход
	case 5:
		q = checkLines();
		if (q != -1) {
			moves.push_back(q);
			row = q / n;
			col = q % n;
			break;
		}
		if (b) {
			for (int i = 0; i < n; ++i) {
				bool f = 0;
				for (int j = 0; j < n; ++j) {
					if (!(*field)[i][j]) {
						moves.push_back(i * n + j);
						row = j;
						col = i;
						f = 1;
						break;
					}
				}
				if (f)
					break;
			}
			break;
		}
		if (moves[0] == 4 && moves[4] == 8) {
			switch (moves[2])
			{
			case 1:
				moves.push_back(2);
				row = 2 / n;
				col = 2 % n;
				break;
			case 3:
				moves.push_back(6);
				row = 6 / n;
				col = 6 % n;
				break;
			}
			break;
		}
		if (moves[1] == 4) {
			switch (moves[3])
			{
			case 1:
				x = rand() % 2;
				x = x ? 6 : 8;
				moves.push_back(x);
				row = x / n;
				col = x % n;
				break;
			case 3:
				x = rand() % 2;
				x = x ? 2 : 8;
				moves.push_back(x);
				row = x / n;
				col = x % n;
				break;
			case 5:
				x = rand() % 2;
				x = x ? 0 : 6;
				moves.push_back(x);
				row = x / n;
				col = x % n;
				break;
			case 7:
				x = rand() % 2;
				x = x ? 0 : 2;
				moves.push_back(x);
				row = x / n;
				col = x % n;
				break;
			}
		}
		break;
		// 4 ход
	case 7:
		q = checkLines();
		if (q != -1) {
			moves.push_back(q);
			row = q / n;
			col = q % n;
			break;
		}
		// к этому моменту остются 2 свободные ячейка и неважно(!), куда ставить
		// т.к. выше сработала checkLines
		for (int i = 0; i < n; ++i) {
			bool f = 0;
			for (int j = 0; j < n; ++j) {
				if (!(*field)[i][j]) {
					moves.push_back(i * n + j);
					row = j;
					col = i;
					f = 1;
					break;
				}
			}
			if (f)
				break;
		}
		break;
	}
}