#include "field.h"

#include "consts.h"
#include "roadCell.h"

Field::Field()
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
	// ������� ��������� ������ � ������ (��� ��������� ��� ����), ��������� ������� ����� ������� addCell
	// ����� ��������� ����� ������, ���� ����������
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
	for (int i = 1; i < ROWS - 1; ++i) {
		addCell(i, 9);
	}
	addCell(ROWS - 1, 9);
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
