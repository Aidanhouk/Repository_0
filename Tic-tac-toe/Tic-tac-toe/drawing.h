#pragma once

#include <SFML/Graphics.hpp>

// ��������� �����
void drawField(sf::RenderWindow & window, int n);
// ��������� ��������� � �������
void drawFigures(sf::RenderWindow & window, int n, int **field);
// ������������� ���������� �����
void crossFinishLine(sf::RenderWindow & window, int n, int finishLineDirection, int rowOrCol);