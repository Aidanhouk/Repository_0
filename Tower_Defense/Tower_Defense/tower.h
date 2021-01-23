#pragma once

#include <SFML/Graphics.hpp>

#include "consts.h"

class Field;
class Missiles;

// класс башни
class Tower
{
private:
	// тип башни
	int m_type;
	// урон башни
	int m_dmg;
	// указатель на тестуру башни
	sf::Texture * m_towerTexture;
	// координаты башни на поле
	std::pair<int, int> m_position{ -1,-1 };
public:
	Tower(int i, int j, int type, sf::Texture * towersTextures[TOWERS_COUNT]);
	~Tower() {}

	// отрисовка башни
	void drawTower(sf::RenderWindow & window);
	// выстрел
	void shoot(Field &field, Missiles &missiles);

	std::pair<int, int>& getPosition() { return m_position; }
	int getTowerType() const { return m_type; }
};