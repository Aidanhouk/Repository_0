#pragma once

#include <SFML/Graphics.hpp>

// отрисовка сетки
void drawField(sf::RenderWindow & window, int n);
// отрисовка крестиков и ноликов
void drawFigures(sf::RenderWindow & window, int n, int **field);
// перечеркиваем выигрышную линию
void crossFinishLine(sf::RenderWindow & window, int n, int finishLineDirection, int rowOrCol);