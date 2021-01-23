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

		for (int i = 0; i < 5; ++i) {
			addCell(ROWS - 2, i);
		}
		for (int i = ROWS - 3; i > 2; --i) {
			addCell(i, 4);
		}
		for (int i = 5; i < 8; ++i) {
			addCell(3, i);
		}
		for (int i = 4; i < ROWS - 3; ++i) {
			addCell(i, COLS - 4);
		}
		for (int i = COLS - 5; i > 0; --i) {
			addCell(ROWS - 4, i);
		}

		for (int i = ROWS - 5; i > 0; --i) {
			addCell(i, 1);
		}
		for (int i = 2; i < COLS - 1; ++i) {
			addCell(1, i);
		}
		for (int i = 2; i < ROWS; ++i) {
			addCell(i, COLS - 2);
		}
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
	case 4:
	{
		cell = new RoadCell(ROWS, 5);
		m_startCell = cell;
		m_finishCell = cell;

		for (int i = ROWS - 1; i > 0; --i) {
			addCell(i, 5);
		}
		for (int i = 6; i < COLS - 1; ++i) {
			addCell(1, i);
		}
		for (int i = 2; i < ROWS - 1; ++i) {
			addCell(i, COLS - 2);
		}
		for (int i = COLS - 3; i > 0; --i) {
			addCell(ROWS - 2, i);
		}

		for (int i = ROWS - 3; i > 0; --i) {
			addCell(i, 1);
		}
		for (int i = 2; i < 4; ++i) {
			addCell(1, i);
		}
		for (int i = 2; i < ROWS - 3; ++i) {
			addCell(i, 3);
		}
		for (int i = 4; i < COLS - 3; ++i) {
			addCell(ROWS - 4, i);
		}
		for (int i = ROWS - 5; i > 2; --i) {
			addCell(i, COLS - 4);
		}
	}
		break;
	case 5:
	{
		cell = new RoadCell(ROWS, 0);
		m_startCell = cell;
		m_finishCell = cell;

		for (int i = ROWS - 1; i > -1; --i) {
			addCell(i, 0);
		}
		for (int i = 1; i < COLS; ++i) {
			addCell(0, i);
		}
		for (int i = 1; i < 3; ++i) {
			addCell(i, COLS - 1);
		}
		for (int i = COLS - 2; i > 1; --i) {
			addCell(2, i);
		}
		for (int i = 3; i < ROWS; ++i) {
			addCell(i, 2);
		}

		for (int i = 3; i < 5; ++i) {
			addCell(ROWS - 1, i);
		}
		for (int i = ROWS - 2; i > 3; --i) {
			addCell(i, 4);
		}
		for (int i = 5; i < COLS; ++i) {
			addCell(4, i);
		}
		for (int i = 5; i < 7; ++i) {
			addCell(i, COLS - 1);
		}
		for (int i = COLS - 2; i > 5; --i) {
			addCell(6, i);
		}
		for (int i = 7; i < ROWS; ++i) {
			addCell(i, 6);
		}

		for (int i = 7; i < COLS; ++i) {
			addCell(ROWS - 1, i);
		}
	}
		break;
	case 6:
	{
		cell = new RoadCell(ROWS, 0);
		m_startCell = cell;
		m_finishCell = cell;

		for (int i = ROWS - 1; i > -1; --i) {
			addCell(i, 0);
		}
		for (int i = 1; i < COLS; ++i) {
			addCell(0, i);
		}
		for (int i = 1; i < 3; ++i) {
			addCell(i, COLS - 1);
		}
		for (int i = COLS - 2; i > 1; --i) {
			addCell(2, i);
		}
		for (int i = 3; i < ROWS; ++i) {
			addCell(i, 2);
		}

		for (int i = 3; i < 5; ++i) {
			addCell(ROWS - 1, i);
		}
		for (int i = ROWS - 2; i > 3; --i) {
			addCell(i, 4);
		}
		for (int i = 5; i < COLS; ++i) {
			addCell(4, i);
		}
		for (int i = 5; i < 7; ++i) {
			addCell(i, COLS - 1);
		}
		for (int i = COLS - 2; i > 5; --i) {
			addCell(6, i);
		}
		for (int i = 7; i < ROWS; ++i) {
			addCell(i, 6);
		}

		for (int i = 7; i < COLS; ++i) {
			addCell(ROWS - 1, i);
		}
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
