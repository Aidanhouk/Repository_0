#include "field.h"

#include "consts.h"
#include "roadCell.h"

Field::Field(int level)
	:m_level{ level }
{
	// создаем поле ROWS * COLS
	m_field = new int*[ROWS];
	for (int i = 0; i < ROWS; ++i) {
		m_field[i] = new int[COLS] {0};
	}
	// создаем текстуру дороги
	sf::Texture *roadTexture{ new sf::Texture };
	(*roadTexture).loadFromFile("images/field/road.png");
	m_roadTexture = roadTexture;
	// создаем текстуру финишной линии
	sf::Texture *finishLineTexture{ new sf::Texture };
	(*finishLineTexture).loadFromFile("images/field/finishLine.png");
	m_finishLineTexture = finishLineTexture;
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
	delete m_roadTexture;
	delete m_finishLineTexture;
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
	// сначала ставится стартовоя ячейка (она находится вне поля), остальные добавляются через функцию addCell
	// можно построить любую дорогу, зная координаты
	RoadCell *cell;
	switch (m_level)
	{
	case 1:
	{
		cell = new RoadCell(8, -1);
		m_startCell = cell;
		m_finishCell = cell;

		addCell(8, 0);
		addCell(8, 1);
		addCell(8, 2);
		addCell(8, 3);
		addCell(8, 4);

		addCell(7, 4);
		addCell(6, 4);
		addCell(5, 4);
		addCell(4, 4);
		addCell(3, 4);

		addCell(3, 5);
		addCell(3, 6);
		addCell(3, 7);

		addCell(4, 7);
		addCell(5, 7);
		addCell(6, 7);

		addCell(6, 6);
		addCell(6, 5);
		addCell(6, 4);
		addCell(6, 3);
		addCell(6, 2);
		addCell(6, 1);

		addCell(5, 1);
		addCell(4, 1);
		addCell(3, 1);
		addCell(2, 1);
		addCell(1, 1);

		addCell(1, 2);
		addCell(1, 3);
		addCell(1, 4);
		addCell(1, 5);
		addCell(1, 6);
		addCell(1, 7);
		addCell(1, 8);
		addCell(1, 9);

		addCell(2, 9);
		addCell(3, 9);
		addCell(4, 9);
		addCell(5, 9);
		addCell(6, 9);
		addCell(7, 9);
		addCell(8, 9);
		addCell(9, 9);
	}
		break;
	case 2:
	{
		cell = new RoadCell(1, -1);
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
		for (int i = 1; i < ROWS - 1; ++i) {
			addCell(i, 9);
		}
		addCell(ROWS - 2, 10);
	}
		break;
	case 3:
	{
		cell = new RoadCell(ROWS, 1);
		m_startCell = cell;
		m_finishCell = cell;

		for (int i = ROWS - 1; i > 0; --i) {
			addCell(i, 1);
		}
		for (int i = 2; i < COLS - 1; ++i) {
			addCell(1, i);
		}
		for (int i = 2; i < ROWS - 1; ++i) {
			addCell(i, COLS - 2);
		}
		for (int i = COLS - 3; i > 2; --i) {
			addCell(ROWS - 2, i);
		}

		for (int i = ROWS - 3; i > 2; --i) {
			addCell(i, 3);
		}
		for (int i = 4; i < COLS - 3; ++i) {
			addCell(3, i);
		}
		for (int i = 4; i < ROWS - 3; ++i) {
			addCell(i, COLS - 4);
		}
		for (int i = COLS - 5; i > 4; --i) {
			addCell(ROWS - 4, i);
		}

		addCell(ROWS - 5, 5);
	}
		break;
	}
}

void Field::paintRoad(sf::RenderWindow & window)
{
	// рисуем дорогу
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			if (m_field[i][j] == 1) {
				sf::RectangleShape road(sf::Vector2f(W, W));
				road.move(W * j, W * i);
				road.setTexture(m_roadTexture);
				window.draw(road);
			}
		}
	}
	// финишная черта
	sf::RectangleShape finishLine(sf::Vector2f(W, W));
	finishLine.move(W * m_finishCell->getCoordinates().second, W * m_finishCell->getCoordinates().first);
	finishLine.setTexture(m_finishLineTexture);
	window.draw(finishLine);
}
