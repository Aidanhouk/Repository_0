#pragma once

#include <SFML/Graphics.hpp>

class RoadCell;

// класс пол€
class Field
{
private:
	// поле
	int **m_field;
	// указатель на стартовую €чейку дороги (за полем)
	RoadCell *m_startCell;
	// указатель на финишную €чейку дороги
	RoadCell *m_finishCell;
	// текстура дороги
	sf::Texture *m_roadTexture;
	// текстура финиша
	sf::Texture *m_finishLineTexture;
public:
	Field();
	~Field();

	// добавить €чейку в дорогу по координатам
	void addCell(int i, int j);
	// создает дорогу дл€ монстров
	void makeRoad();
	// рисует дорогу
	void paintRoad(sf::RenderWindow &window);
	// провер€ет, свободна ли эта €чейка
	int getCellValue(int i, int j) const { return m_field[i][j]; }
	// если в €чейку поставили башню, нужно это зафиксировать
	int &getCell(int i, int j) { return m_field[i][j]; }

	// возвращает стартовую позицию
	RoadCell * getStartPos() { return m_startCell; }
	// возвращает финишную €чейку
	RoadCell * getFinishPos() { return m_finishCell; }
	// возвращает указатель на поле
	int** getField() const { return m_field; }
};