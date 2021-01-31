#pragma once

#include <SFML/Graphics.hpp>

class RoadCell;
class FieldCell;
class Tower;

// класс поля
class Field
{
private:
	// уровень/карта
	int m_level;
	// поле
	FieldCell **m_field;
	// указатель на стартовую ячейку дороги (за полем)
	RoadCell *m_startCell{ nullptr };
	// указатель на финишную ячейку дороги
	RoadCell *m_finishCell{ nullptr };
	// текстура дороги
	sf::Texture *m_roadTexture;
	// текстура финиша
	sf::Texture *m_finishLineTexture;
public:
	Field();
	~Field();

	// добавить ячейку в дорогу по координатам
	void addRoadCell(int i, int j);
	// создает дорогу для монстров
	void makeRoad();
	// рисует дорогу
	void paintRoad();
	// отрисовка дальности поражения
	void drawRange(int i, int j);

	void addTowerOnCell(int i, int j, Tower * tower);
	void removeTowerFromCell(int i, int j) { addTowerOnCell(i, j, nullptr); }
	Tower * getTowerOnCell(int i, int j);
	int getCellValue(int i, int j) const;
	void setCellValue(int i, int j, int typeOfCell);
	RoadCell * getStartPos() { return m_startCell; }
	RoadCell * getFinishPos() { return m_finishCell; }
};