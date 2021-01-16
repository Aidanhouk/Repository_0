#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "roadCell.h"

// класс поля
class Field
{
private:
	// поле
	int **m_field;
	// список ячеек дороги
	std::list<RoadCell*> m_roadCells;
public:
	Field();
	~Field();

	// добавить ячейку в дорогу по координатам
	void addCell(int i, int j);
	// создает дорогу для монстров
	void makeRoad();
	// рисует дорогу
	void paintRoad(sf::RenderWindow &window);
	// проверяет, свободна ли эта ячейка
	int getCellValue(int i, int j) const { return m_field[i][j]; }
	// если в ячейку поставили башню, нужно это зафиксировать
	int &getCell(int i, int j) { return m_field[i][j]; }

	// возвращает стартовую позицию
	RoadCell * getStartPos() { return m_roadCells.front(); }
	// возвращает список ячеек дороги
	std::list<RoadCell*> & getRoad() { return m_roadCells; }
	// возвращает указатель на поле
	int** getField() const { return m_field; }
};