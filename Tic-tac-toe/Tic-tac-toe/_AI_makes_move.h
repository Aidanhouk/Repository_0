#pragma once

#include <vector>

// ��������� ������ �����, ������ ���� + ���������� ������ ������ � �������, ���� ��������� ������
void _AI_makes_move(std::vector<int> &moves, int **field, int n, int &row, int &col);
// ���������, ���� �� ������ � n-1 ����������� ��������� � 1 ������
// �� ����� ������, ����� ���� ��������, ���� �� ���� �������� ���������
int checkLines(int **field, int n, int markAI);