#include "_AI_makes_move.h"

#include <ctime>

void _AI_makes_move(std::vector<int> &moves, int **field, int n, int &row, int &col)
{
	srand(static_cast<unsigned int>(time(0)));
	rand();

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
		q = checkLines(field, n, markAI);
		if (q != -1) {
			moves.push_back(q);
			row = q / n;
			col = q % n;
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
					q = checkLines(field, n, markAI);
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
					q = checkLines(field, n, markAI);
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
							if (!field[i][j]) {
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
			// если AI должен ставить нолик
			else {
				// перменная для рандома
				int x;
				// нужно для одного из случаев
				static bool b{ 0 };
				switch (moves.size())
				{
					// 1 ход
				case 1:
					q = checkLines(field, n, markAI);
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
						// тут захардкорим левый верхний угол
						moves.push_back(0);
						row = 0 / n;
						col = 0 % n;
						break;
					}
					break;
					// 2 ход
				case 3:
					q = checkLines(field, n, markAI);
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
					q = checkLines(field, n, markAI);
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
								if (!field[i][j]) {
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
					q = checkLines(field, n, markAI);
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
							if (!field[i][j]) {
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
		}
	}
}