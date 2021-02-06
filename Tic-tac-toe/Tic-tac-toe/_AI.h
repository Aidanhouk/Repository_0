#pragma once

#include <vector>

class AI
{
private:
	// ������ �� ������� ������ AI, 1 - ��������, 2 - ������
	int m_markAI;
	// ���������, ���� �� ������ � n-1 ����������� ��������� � 1 ������
	// �� ����� ������, ����� ���� ��������, ���� �� ���� �������� ���������
	int checkLines();
	// ������ ��� ����������
	void _AIMovesCrosses(std::vector<int> &moves, int &row, int &col);
	// ������ ��� ��������
	void _AIMovesNoughts(std::vector<int> &moves, int &row, int &col);
public:
	// � ��������� - ������, �� ������� ������ AI
	AI(int markAI) : m_markAI{ markAI } {}
	~AI() {}

	int getAIMark() const { return m_markAI; }

	// AI ������ ��� + ���������� ����������, ���� �������� ������
	void _AI_makes_move(int &row, int &col);
};