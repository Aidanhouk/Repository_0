#pragma once
#include <vector>

// принимает вектор ходов, размер поля + возвращает номера строки и столбца, куда поставить фигуру
void _AI_makes_move(std::vector<int> &moves, int **field, int n, int &row, int &col);