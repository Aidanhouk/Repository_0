#pragma once

#include <vector>

// принимает вектор ходов, размер поля + возвращает номера строки и столбца, куда поставить фигуру
void _AI_makes_move(std::vector<int> &moves, int **field, int n, int &row, int &col);
// проверяет, если ли строка с n-1 одинаковыми символами и 1 пустым
// ее нужно занять, чтобы либо выиграть, либо не дать выиграть оппоненту
int checkLines(int **field, int n, int markAI);