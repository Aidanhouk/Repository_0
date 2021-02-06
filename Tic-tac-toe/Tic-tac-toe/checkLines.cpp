#include "_AI.h"

#include "globals.h"
#include "field.h"

int AI::checkLines()
{
	// номер ячейки, чтобы не дать завершить линию оппоненту
	int notMine{ -1 };

	// проверяем каждый столбец
	for (int i = 0; i < n; ++i) {
		// кол-во пустых ячеек; занятых тем же знаком, что и у AI; занятых другим знаком
		int blanks{ 0 }, sameAIMarks{ 0 }, notAIMarks{ 0 };
		for (int j = 0; j < n; ++j) {
			if ((*field)[i][j] == 0) {
				++blanks;
				continue;
			}
			if ((*field)[i][j] == m_markAI) {
				++sameAIMarks;
			}
			else {
				++notAIMarks;
			}
		}
		// если всего 1 пустая ячейка
		if (blanks == 1) {
			// если на всех остальных стоит знак AI
			if (sameAIMarks == n - 1) {
				// найдем пустую клетку и вернем ее
				// тут макс 5 ячеек нужно перебрать, так что поставим еще цикл
				for (int j = 0; j < n; ++j) {
					if (!(*field)[i][j]) {
						return i + j * n;
					}
				}
			}
			// если на всех остальных стоит знак, противоположный знаку AI
			if (notAIMarks == n - 1) {
				for (int j = 0; j < n; ++j) {
					if (!(*field)[i][j]) {
						notMine = i + j * n;
						break;
					}
				}
			}
		}
	}

	// проверяем каждую строку
	for (int i = 0; i < n; ++i) {
		// кол-во пустых ячеек; занятых тем же знаком, что и у AI; занятых другим знаком
		int blanks{ 0 }, sameAIMarks{ 0 }, notAIMarks{ 0 };
		for (int j = 0; j < n; ++j) {
			if ((*field)[j][i] == 0) {
				++blanks;
				continue;
			}
			if ((*field)[j][i] == m_markAI) {
				++sameAIMarks;
			}
			else {
				++notAIMarks;
			}
		}
		// если всего 1 пустая ячейка
		if (blanks == 1) {
			// если на всех остальных стоит знак AI
			if (sameAIMarks == n - 1) {
				// найдем пустую клетку и вернем ее
				for (int j = 0; j < n; ++j) {
					if (!(*field)[j][i]) {
						return i * n + j;
					}
				}
			}
			// если на всех остальных стоит знак, противоположный знаку AI
			if (notAIMarks == n - 1) {
				for (int j = 0; j < n; ++j) {
					if (!(*field)[j][i]) {
						notMine = i * n + j;
						break;
					}
				}
			}
		}
	}

	// проверяем 1 диагональ
	{
		// кол-во пустых ячеек; занятых тем же знаком, что и у AI; занятых другим знаком
		int blanks{ 0 }, sameAIMarks{ 0 }, notAIMarks{ 0 };
		for (int i = 0; i < n; ++i) {
			if ((*field)[i][i] == 0) {
				++blanks;
				continue;
			}
			if ((*field)[i][i] == m_markAI) {
				++sameAIMarks;
			}
			else {
				++notAIMarks;
			}
		}
		// если всего 1 пустая ячейка
		if (blanks == 1) {
			// если на всех остальных стоит знак AI
			if (sameAIMarks == n - 1) {
				// найдем пустую клетку и вернем ее
				for (int i = 0; i < n; ++i) {
					if (!(*field)[i][i]) {
						return i * n + i;
					}
				}
			}
			// если на всех остальных стоит знак, противоположный знаку AI
			if (notAIMarks == n - 1) {
				for (int i = 0; i < n; ++i) {
					if (!(*field)[i][i]) {
						notMine = i * n + i;
						break;
					}
				}
			}
		}
	}

	// проверяем 2 диагональ
	{
		// кол-во пустых ячеек; занятых тем же знаком, что и у AI; занятых другим знаком
		int blanks{ 0 }, sameAIMarks{ 0 }, notAIMarks{ 0 };
		for (int i = 0; i < n; ++i) {
			if ((*field)[i][n - 1 - i] == 0) {
				++blanks;
				continue;
			}
			if ((*field)[i][n - 1 - i] == m_markAI) {
				++sameAIMarks;
			}
			else {
				++notAIMarks;
			}
		}
		// если всего 1 пустая ячейка
		if (blanks == 1) {
			// если на всех остальных стоит знак AI
			if (sameAIMarks == n - 1) {
				// найдем пустую клетку и вернем ее
				for (int i = 0; i < n; ++i) {
					if (!(*field)[n - 1 - i][i]) {
						return n * i + (n - 1 - i);
					}
				}
			}
			// если на всех остальных стоит знак, противоположный знаку AI
			if (notAIMarks == n - 1) {
				for (int i = 0; i < n; ++i) {
					if (!(*field)[n - 1 - i][i]) {
						notMine = n * i + (n - 1 - i);
						break;
					}
				}
			}
		}
	}

	return notMine;
}