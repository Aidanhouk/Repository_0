#include "field.h"

#include "globals.h"

Field::Field()
{
	// ������� ���� ������������ nxn
	m_field = new int*[n];
	for (int i = 0; i < n; ++i) {
		m_field[i] = new int[n] {};
	}
	m_blanks = n * n;
	m_moves.reserve(n * n);
}

Field::~Field()
{
	for (int i = 0; i < n; ++i) {
		delete[] m_field[i];
	}
	delete[] m_field;
}

int Field::finishedLineCheck()
{
	bool f;
	for (int i = 0; i < n; ++i) {
		f = 1;
		// ���� 1 ������� ������ - �� ������ ������
		if ((*field)[i][0] != 0) {
			// �������� �� ������� �������� � i-�� ������
			for (int j = 1; j < n; ++j) {
				if ((*field)[i][j] != (*field)[i][0]) {
					f = 0;
					break;
				}
			}
			if (f) {
				// ����� ���� field[i][0]
				m_rowOrCol = i, m_finishLineDirection = 1;
				return (*field)[i][0];
			}
		}
		f = 1;
		if (field[0][i] != 0) {
			// �������� �� ������� �������� � i-�� �������
			for (int j = 1; j < n; ++j) {
				if ((*field)[j][i] != (*field)[0][i]) {
					f = 0;
					break;
				}
			}
			if (f) {
				// ����� ���� field[0][i]
				m_rowOrCol = i, m_finishLineDirection = 2;
				return (*field)[0][i];
			}
		}
	}
	// �������� ������ ���������
	f = 1;
	if ((*field)[0][0] != 0) {
		for (int i = 0; i < n; ++i) {
			if ((*field)[i][i] != (*field)[0][0]) {
				f = 0;
				break;
			}
		}
		if (f) {
			// ����� ���� field[0][0]
			m_finishLineDirection = 3;
			return (*field)[0][0];
		}
	}
	f = 1;
	if ((*field)[n - 1][0] != 0) {
		for (int i = 0; i < n; ++i) {
			if ((*field)[n - 1 - i][i] != (*field)[n - 1][0]) {
				f = 0;
				break;
			}
		}
		if (f) {
			// ����� ���� field[n - 1][0]
			m_finishLineDirection = 4;
			return (*field)[n - 1][0];
		}
	}
	return 0;
}