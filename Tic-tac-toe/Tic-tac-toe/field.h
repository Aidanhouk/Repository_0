#pragma once

#include <vector>

class Field
{
private:
	// ���� ����
	int **m_field;
	// ������� �������� ������ �����
	int m_blanks;
	// �����, ����� ������������ ���������� �����
	int m_rowOrCol, m_finishLineDirection;
	// ����� ������ ������ �������� (1 - ��������, 2 - ������)
	bool m_turn{ 1 };
	// ���� ����� ������������ ��� ����, ����� ��� ������ AI
	std::vector<int> m_moves;
public:
	Field();
	~Field();

	// ���������, ���� �� �����, ����������� 1 ����� �����
	int finishedLineCheck();
	// ��������� ���-�� ������ ����� (���� ������ ���)
	void decreaseBlanks() { --m_blanks; }
	// �������� �� �����
	bool isDraw() { return !m_blanks; }
	// ��� ��������, ������ �������� ������� ������ ������
	void changeTurn() { m_turn = !m_turn; }

	std::vector<int> &getMovesVector() { return m_moves; }
	void setMovesVector(std::vector<int> &vc) { m_moves = vc; }
	bool getTurn() const { return m_turn; }
	int getRowOrCol() const { return m_rowOrCol; }
	int getFinishLineDirection() const { return m_finishLineDirection; }

	int* operator[](const int index) { return m_field[index]; }
};