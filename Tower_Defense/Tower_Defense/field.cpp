#include "field.h"

#include "consts.h"
#include "globals.h"
#include "roadCell.h"
#include "fieldCell.h"
#include "tower.h"

Field::Field()
	:m_level{ level }
{
	// создаем поле ROWS * COLS
	m_field = new FieldCell*[ROWS];
	for (int i = 0; i < ROWS; ++i) {
		m_field[i] = new FieldCell[COLS];
		for (int j = 0; j < COLS; ++j) {
			m_field[i][j].setPosition(i, j);
		}
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

void Field::addRoadCell(int i, int j)
{
	RoadCell *cell = new RoadCell(i, j);
	m_finishCell->setNextCell(cell);
	cell->setPrevCell(m_finishCell);
	m_finishCell = cell;
	m_field[i][j] = 1;
}

void Field::paintRoad()
{
	// рисуем дорогу
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			if (m_field[i][j] == 1) {
				sf::RectangleShape road(sf::Vector2f(W, W));
				road.move(W * j, W * i);
				road.setTexture(m_roadTexture);
				(*window).draw(road);
			}
		}
	}
	// финишная черта
	sf::RectangleShape finishLine(sf::Vector2f(W, W));
	finishLine.move(W * m_finishCell->getCoordinates().second, W * m_finishCell->getCoordinates().first);
	finishLine.setTexture(m_finishLineTexture);
	(*window).draw(finishLine);
}

void Field::drawRange(int i, int j)
{
	int range{ getTowerOnCell(i, j)->getRange() };
	sf::RectangleShape border1(sf::Vector2f(W * (1 + 2 * range), 5));
	border1.move(W * (j - range), W * (i - range));
	sf::RectangleShape border2(sf::Vector2f(W * (1 + 2 * range), 5));
	border2.move(W * (j - range), W * (i + 1 + range) - 5);
	sf::RectangleShape border3(sf::Vector2f(5, W * (1 + 2 * range)));
	border3.move(W * (j - range), W * (i - range));
	sf::RectangleShape border4(sf::Vector2f(5, W * (1 + 2 * range)));
	border4.move(W * (j + 1 + range) - 5, W * (i - range));
	if (getTowerOnCell(i, j)->getTowerType() > 6) {
		border1.setFillColor(sf::Color::Green);
		border2.setFillColor(sf::Color::Green);
		border3.setFillColor(sf::Color::Green);
		border4.setFillColor(sf::Color::Green);
	}
	else {
		border1.setFillColor(sf::Color::White);
		border2.setFillColor(sf::Color::White);
		border3.setFillColor(sf::Color::White);
		border4.setFillColor(sf::Color::White);
	}
	(*window).draw(border1);
	(*window).draw(border2);
	(*window).draw(border3);
	(*window).draw(border4);
}

void Field::addTowerOnCell(int i, int j, Tower * tower)
{
	m_field[i][j].setTowerOnCell(tower);
}

Tower * Field::getTowerOnCell(int i, int j)
{
	return m_field[i][j].getTowerOnCell();
}

int Field::getCellValue(int i, int j) const
{
	return m_field[i][j].getTypeOfCell();
}

void Field::setCellValue(int i, int j, int typeOfCell)
{
	m_field[i][j].setTypeOfCell(typeOfCell);
}
