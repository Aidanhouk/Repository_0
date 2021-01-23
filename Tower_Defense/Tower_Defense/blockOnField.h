#pragma once

#include <SFML/Graphics.hpp>

#include "consts.h"

class RoadCell;
class BlocksControl;

class BlockOnField
{
private:
	// тип блока
	int m_type;
	// здоровье блока
	int m_hp;
	// указатель на тестуру блока
	sf::Texture * m_blockTexture;
	// ячейка дороги, на которой стоит блок
	RoadCell * m_roadCell;
	// укзатель на объект, контролирующий блоки
	BlocksControl * m_blocksControl;
public:
	BlockOnField(int type, sf::Texture * blocksTextures[FIELD_BLOCKS_COUNT], BlocksControl * blocksControl);
	~BlockOnField() {}

	// отрисовка блока
	void drawBlock(sf::RenderWindow & window);
	// получение урона
	void getDamage(int dmg);
	// отрисовка шкалы здоровья
	void drawHPBar(sf::RenderWindow &window);

	RoadCell * getCell() { return m_roadCell; }
	void setCell(RoadCell * cell) { m_roadCell = cell; }
	int getType() const { return m_type; }
};