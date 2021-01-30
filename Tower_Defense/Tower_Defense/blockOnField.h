#pragma once

#include <SFML/Graphics.hpp>

#include "consts.h"

class RoadCell;
class BlocksControl;

// класс блока на поле
class BlockOnField
{
private:
	// тип блока
	int m_type;
	// здоровье блока
	int m_hp;
	// указатель на тестуру блока
	sf::Texture * m_blockTexture;
	// укзатель на объект, контролирующий блоки
	BlocksControl * m_blocksControl;
	// массив с указателями на ячейки, на которых находится блок, макс - 2
	RoadCell * m_roadCells[2]{ nullptr };
public:
	BlockOnField(int type, sf::Texture * blocksTextures[FIELD_BLOCKS_COUNT], BlocksControl * blocksControl);
	~BlockOnField() {}

	// отрисовка блока
	void drawBlock();
	// получение урона
	void getDamage(int dmg);
	// отрисовка шкалы здоровья
	void drawHPBar();
	// добавить клетку в m_roadCells
	void addCell(RoadCell * cell) { m_roadCells[0] = cell; }
	// добавить 2 клетку в m_roadCells
	void addCell2(RoadCell * cell) { m_roadCells[1] = cell; }
	// 1 клетка на которой, находится блок
	RoadCell * getCell() { return m_roadCells[0]; }
	// 2 клетка на которой, находится блок
	RoadCell * getCell2() { return m_roadCells[1]; }

	int getType() const { return m_type; }
	int getHP() const { return m_hp; }
};