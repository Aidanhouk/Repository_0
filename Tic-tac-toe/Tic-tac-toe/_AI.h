#pragma once

#include <vector>

class AI
{
private:
	// ������ �� ������� ������ AI
	bool m_markAI;
	// ���������, ���� �� ������ � n-1 ����������� ��������� � 1 ������
	// �� ����� ������, ����� ���� ��������, ���� �� ���� �������� ���������
	int checkLines();
	// ������ ��� ����������
	void _AIMovesCrosses(std::vector<int> &moves, int &row, int &col);
	// ������ ��� ��������
	void _AIMovesNoughts(std::vector<int> &moves, int &row, int &col);
public:
	// � ��������� - ������, �� ������� ������ AI
	AI(bool markAI) : m_markAI{ markAI } {}
	~AI() {}

	bool getAIMark() const { return m_markAI; }

	// AI ������ ��� + ���������� ����������, ���� �������� ������
	void _AI_makes_move(int &row, int &col);
};