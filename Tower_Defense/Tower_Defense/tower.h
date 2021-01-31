#pragma once

#include <SFML/Graphics.hpp>

#include "consts.h"

class Missiles;
class RoadCell;

// класс башни
class Tower
{
private:
	// тип башни
	int m_type;
	// дальность поражения
	int m_range{ 1 };
	// сколько рядом бафающих башен на урон
	int m_damageTowers{ 0 };
	// урон башни
	double m_dmg;
	// указатель на тестуру башни
	sf::Texture * m_towerTexture;
	// координаты башни на поле
	std::pair<int, int> m_position{ -1,-1 };
	// текстуры бафов
	sf::Texture *m_buffTextures[4];
	// список клеток, по которым может стрелять башня
	std::vector<RoadCell*> m_cellsInRange;
	// изменить радиус поражения
	void changeRange();
public:
	Tower(int i, int j, int type, sf::Texture * towersTextures[TOWERS_COUNT], sf::Texture * buffTextures[4]);
	~Tower() {}

	// отрисовка башни
	void drawTower();
	// выстрел
	void shoot(Missiles &missiles);
	// изменить урон врага
	void changeDamage();
	// проверить, есть рядом бафающие башни
	void checkForBuffs();

	std::pair<int, int>& getPosition() { return m_position; }
	int getTowerType() const { return m_type; }
	int getRange() const { return m_range; }
};