#include "field.h"

#include "consts.h"

Field::Field()
{
	// создаем поле ROWS * COLS
	m_field = new int*[ROWS];
	for (int i = 0; i < ROWS; ++i) {
		m_field[i] = new int[COLS] {0};
	}
}

Field::~Field()
{
	// освобождение памяти у дороги, каждая клетка освобождает память у следующей
	delete m_startCell;
	// освобождение памяти под поле
	for (int i = 0; i < ROWS; ++i) {
		delete[] m_field[i];
	}
	delete[] m_field;
}

void Field::addCell(int i, int j)
{
	RoadCell *cell = new RoadCell(i, j);
	m_finishCell->setNextCell(cell);
	cell->setPrevCell(m_finishCell);
	m_finishCell = cell;
	m_field[i][j] = 1;
}

void Field::makeRoad()
{
	// добавим стартовую ячейку в дорогу (она находится вне поля), остальные добавим через функцию addCell
	// можно построить любую дорогу, зная координаты
	RoadCell *cell = new RoadCell(1, -1);
	m_startCell = cell;
	m_finishCell = cell;

	addCell(1, 0);
	for (int i = 1; i < ROWS - 1; ++i) {
		addCell(i, 1);
	}
	addCell(ROWS - 2, 2);
	for (int i = ROWS - 2; i > 0; --i) {
		addCell(i, 3);
	}
	addCell(1, 4);
	for (int i = 1; i < ROWS - 1; ++i) {
		addCell(i, 5);
	}
	addCell(ROWS - 2, 6);
	for (int i = ROWS - 2; i > 0; --i) {
		addCell(i, 7);
	}
	addCell(1, 8);
}

void Field::paintRoad(sf::RenderWindow & window)
{
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			if (m_field[i][j] == 1) {
				// рисуем дорогу
				sf::RectangleShape road(sf::Vector2f(W, W));
				road.move(j * static_cast<float>(W), i * static_cast<float>(W));
				road.setFillColor(sf::Color(150, 125, 60));
				window.draw(road);
			}
		}
	}
	// финишная черта / красный крестик
	sf::RectangleShape finish1(sf::Vector2f(W >> 1, 5));
	finish1.move(m_finishCell->getCoordinates().second * (float)(W)+W / 3, m_finishCell->getCoordinates().first * (float)(W)+W / 3);
	finish1.rotate(45.f);
	finish1.setFillColor(sf::Color::Red);
	window.draw(finish1);
	sf::RectangleShape finish2(sf::Vector2f(W >> 1, 5));
	finish2.move(m_finishCell->getCoordinates().second * (float)(W)+W / 3 - 3, m_finishCell->getCoordinates().first * (float)(W)+W *0.7 - 2);
	finish2.rotate(-45.f);
	finish2.setFillColor(sf::Color::Red);
	window.draw(finish2);
}
