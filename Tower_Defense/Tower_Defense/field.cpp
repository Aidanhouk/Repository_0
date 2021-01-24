#include "field.h"

#include "consts.h"
#include "roadCell.h"

Field::Field(int level)
	:m_level{ level }
{
	// ������� ���� ROWS * COLS
	m_field = new int*[ROWS];
	for (int i = 0; i < ROWS; ++i) {
		m_field[i] = new int[COLS] {0};
	}
	// ������� �������� ������
	sf::Texture *roadTexture{ new sf::Texture };
	(*roadTexture).loadFromFile("images/field/road.png");
	m_roadTexture = roadTexture;
	// ������� �������� �������� �����
	sf::Texture *finishLineTexture{ new sf::Texture };
	(*finishLineTexture).loadFromFile("images/field/finishLine.png");
	m_finishLineTexture = finishLineTexture;
}

Field::~Field()
{
	// ������������ ������ � ������, ������ ������ ����������� ������ � ���������
	delete m_startCell;
	// ������������ ������ ��� ����
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
	// ������� �������� ��������� ������ (��� ��������� ��� ����), ��������� ����������� ����� ������� addCell
	// ����� ��������� ����� ������, ���� ����������
	RoadCell *cell;
	switch (m_level)
	{
	case 1:
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
	case 2:
	{
		cell = new RoadCell(ROWS, 4);
		m_startCell = cell;
		m_finishCell = cell;

		for (int i = ROWS - 1; i > -1; --i) {
			addCell(i, COLS - 7);
		}
		for (int i = COLS - 8; i > COLS - 10; --i) {
			addCell(0, i);
		}

		for (int i = 1; i < ROWS; ++i) {
			addCell(i, COLS - 9);
		}
		for (int i = COLS - 10; i > -1; --i) {
			addCell(ROWS - 1, i);
		}

		for (int i = ROWS - 2; i > ROWS - 4; --i) {
			addCell(i, 0);
		}
		for (int i = 1; i < COLS; ++i) {
			addCell(ROWS - 3, i);
		}
		for (int i = ROWS - 2; i < ROWS; ++i) {
			addCell(i, COLS - 1);
		}

		for (int i = COLS - 2; i > COLS - 4; --i) {
			addCell(ROWS - 1, i);
		}
		for (int i = ROWS - 2; i > -1; --i) {
			addCell(i, COLS -3);
		}

		for (int i = COLS - 4; i > COLS - 6; --i) {
			addCell(0, i);
		}
		for (int i = 1; i < ROWS; ++i) {
			addCell(i, COLS - 5);
		}

		addCell(ROWS - 1, COLS - 6);
	}
		break;
	case 3:
	{
		cell = new RoadCell(ROWS - 4, -1);
		m_startCell = cell;
		m_finishCell = cell;

		addCell(ROWS - 4, 0);
		addCell(ROWS - 3, 0);
		addCell(ROWS - 3, 1);
		addCell(ROWS - 2, 1);
		addCell(ROWS - 2, 2);
		addCell(ROWS - 1, 2);
		for (int i = 3; i < COLS - 2; ++i) {
			addCell(ROWS - 1, i);
		}
		addCell(ROWS - 2, COLS - 3);
		addCell(ROWS - 2, COLS - 2);
		addCell(ROWS - 3, COLS - 2);
		addCell(ROWS - 3, COLS - 1);
		for (int i = ROWS - 4; i > 1; --i) {
			addCell(i, COLS - 1);
		}
		addCell(2, COLS - 2);
		addCell(1, COLS - 2);
		addCell(1, COLS - 3);
		addCell(0, COLS - 3);
		for (int i = COLS - 4; i > 1; --i) {
			addCell(0, i);
		}
		addCell(1, 2);
		addCell(1, 1);
		addCell(2, 1);
		addCell(2, 0);
		for (int i = 3; i < 5; ++i) {
			addCell(i, 0);
		}

		for (int i = 1; i < 3; ++i) {
			addCell(4, i);
		}
		addCell(3, 2);
		addCell(3, 3);
		addCell(2, 3);
		for (int i = 4; i < COLS - 3; ++i) {
			addCell(2, i);
		}
		addCell(3, COLS - 4);
		for (int i = 3; i < ROWS - 3; ++i) {
			addCell(i, COLS - 3);
		}
		addCell(ROWS - 4, COLS - 4);
		for (int i = COLS - 4; i > 2; --i) {
			addCell(ROWS - 3, i);
		}
		addCell(ROWS - 4, 3);
		addCell(ROWS - 4, 2);
		for (int i = 2; i > -1; --i) {
			addCell(ROWS - 5, i);
		}
	}
		break;
	case 4:
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
		for (int i = 5; i < COLS - 3; ++i) {
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
	// ������ ������
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
	// �������� �����
	sf::RectangleShape finishLine(sf::Vector2f(W, W));
	finishLine.move(W * m_finishCell->getCoordinates().second, W * m_finishCell->getCoordinates().first);
	finishLine.setTexture(m_finishLineTexture);
	window.draw(finishLine);
}
