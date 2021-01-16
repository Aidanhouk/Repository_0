#include "checkLines.h"

int checkLines(int **field, int n, int markAI)
{
	// ����� ������, ����� �� ���� ��������� ����� ���������
	int notMine{ -1 };
	// �������� markAI �� ���� 0/1 � 1/2
	markAI = markAI ? 1 : 2;

	// ��������� ������ �������
	for (int i = 0; i < n; ++i) {
		// ���-�� ������ �����; ������� ��� �� ������, ��� � � AI; ������� ������ ������
		int blanks{ 0 }, sameAIMarks{ 0 }, notAIMarks{ 0 };
		for (int j = 0; j < n; ++j) {
			if (field[i][j] == 0) {
				++blanks;
				continue;
			}
			if (field[i][j] == markAI) {
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
					if (!field[i][j]) {
						return i + j * n;
					}
				}
			}
			// ���� �� ���� ��������� ����� ����, ��������������� ����� AI
			if (notAIMarks == n - 1) {
				for (int j = 0; j < n; ++j) {
					if (!field[i][j]) {
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
			if (field[j][i] == 0) {
				++blanks;
				continue;
			}
			if (field[j][i] == markAI) {
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
					if (!field[j][i]) {
						return i * n + j;
					}
				}
			}
			// ���� �� ���� ��������� ����� ����, ��������������� ����� AI
			if (notAIMarks == n - 1) {
				for (int j = 0; j < n; ++j) {
					if (!field[j][i]) {
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
			if (field[i][i] == 0) {
				++blanks;
				continue;
			}
			if (field[i][i] == markAI) {
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
					if (!field[i][i]) {
						return i * n + i;
					}
				}
			}
			// ���� �� ���� ��������� ����� ����, ��������������� ����� AI
			if (notAIMarks == n - 1) {
				for (int i = 0; i < n; ++i) {
					if (!field[i][i]) {
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
			if (field[i][n - 1 - i] == 0) {
				++blanks;
				continue;
			}
			if (field[i][n - 1 - i] == markAI) {
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
					if (!field[n - 1 - i][i]) {
						return n * i + (n - 1 - i);
					}
				}
			}
			// ���� �� ���� ��������� ����� ����, ��������������� ����� AI
			if (notAIMarks == n - 1) {
				for (int i = 0; i < n; ++i) {
					if (!field[n - 1 - i][i]) {
						notMine = n * i + (n - 1 - i);
						break;
					}
				}
			}
		}
	}

	return notMine;
}