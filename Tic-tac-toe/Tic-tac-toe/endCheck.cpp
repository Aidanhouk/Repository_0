#include <SFML/Graphics.hpp>
#include "endCheck.h"

int finishedLineCheck(int **field, const int n, int &rowOrCol, int &dir)
{
	bool f;
	for (int i = 0; i < n; ++i) {
		f = 1;
		// ���� 1 ������� ������ - �� ������ ������
		if (field[i][0] != 0) {
			// �������� �� ������� �������� � i-�� ������
			for (int j = 1; j < n; ++j) {
				if (field[i][j] != field[i][0]) {
					f = 0;
					break;
				}
			}
			if (f) {
				// ����� ���� field[i][0]
				rowOrCol = i, dir = 1;
				return field[i][0];
			}
		}
		f = 1;
		if (field[0][i] != 0) {
			// �������� �� ������� �������� � i-�� �������
			for (int j = 1; j < n; ++j) {
				if (field[j][i] != field[0][i]) {
					f = 0;
					break;
				}
			}
			if (f) {
				// ����� ���� field[0][i]
				rowOrCol = i, dir = 2;
				return field[0][i];
			}
		}
	}
	// �������� ������ ���������
	f = 1;
	if (field[0][0] != 0) {
		for (int i = 0; i < n; ++i) {
			if (field[i][i] != field[0][0]) {
				f = 0;
				break;
			}
		}
		if (f) {
			// ����� ���� field[0][0]
			dir = 3;
			return field[0][0];
		}
	}
	f = 1;
	if (field[n - 1][0] != 0) {
		for (int i = 0; i < n; ++i) {
			if (field[n - 1 - i][i] != field[n - 1][0]) {
				f = 0;
				break;
			}
		}
		if (f) {
			// ����� ���� field[n - 1][0]
			dir = 4;
			return field[n - 1][0];
		}
	}
	return 0;
}