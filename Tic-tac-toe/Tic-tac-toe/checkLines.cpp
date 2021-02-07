#include "_AI.h"

#include "globals.h"
#include "field.h"

int AI::checkLines()
{
	// ����� ������, ����� �� ���� ��������� ����� ���������
	int notMine{ -1 };

	// ��������� ������ �������
	for (int i = 0; i < n; ++i) {
		// ���-�� ������ �����; ������� ��� �� ������, ��� � � AI; ������� ������ ������
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
		// ���� ����� 1 ������ ������
		if (blanks == 1) {
			// ���� �� ���� ��������� ����� ���� AI
			if (sameAIMarks == n - 1) {
				// ������ ������ ������ � ������ ��
				// ��� ���� 5 ����� ����� ���������, ��� ��� �������� ��� ����
				for (int j = 0; j < n; ++j) {
					if (!(*field)[i][j]) {
						return i + j * n;
					}
				}
			}
			// ���� �� ���� ��������� ����� ����, ��������������� ����� AI
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

	// ��������� ������ ������
	for (int i = 0; i < n; ++i) {
		// ���-�� ������ �����; ������� ��� �� ������, ��� � � AI; ������� ������ ������
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
		// ���� ����� 1 ������ ������
		if (blanks == 1) {
			// ���� �� ���� ��������� ����� ���� AI
			if (sameAIMarks == n - 1) {
				// ������ ������ ������ � ������ ��
				for (int j = 0; j < n; ++j) {
					if (!(*field)[j][i]) {
						return i * n + j;
					}
				}
			}
			// ���� �� ���� ��������� ����� ����, ��������������� ����� AI
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

	// ��������� 1 ���������
	{
		// ���-�� ������ �����; ������� ��� �� ������, ��� � � AI; ������� ������ ������
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
		// ���� ����� 1 ������ ������
		if (blanks == 1) {
			// ���� �� ���� ��������� ����� ���� AI
			if (sameAIMarks == n - 1) {
				// ������ ������ ������ � ������ ��
				for (int i = 0; i < n; ++i) {
					if (!(*field)[i][i]) {
						return i * n + i;
					}
				}
			}
			// ���� �� ���� ��������� ����� ����, ��������������� ����� AI
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

	// ��������� 2 ���������
	{
		// ���-�� ������ �����; ������� ��� �� ������, ��� � � AI; ������� ������ ������
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
		// ���� ����� 1 ������ ������
		if (blanks == 1) {
			// ���� �� ���� ��������� ����� ���� AI
			if (sameAIMarks == n - 1) {
				// ������ ������ ������ � ������ ��
				for (int i = 0; i < n; ++i) {
					if (!(*field)[n - 1 - i][i]) {
						return n * i + (n - 1 - i);
					}
				}
			}
			// ���� �� ���� ��������� ����� ����, ��������������� ����� AI
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