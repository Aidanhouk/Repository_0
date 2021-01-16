#pragma once

#include <SFML/Graphics.hpp>

#include "field.h"
#include"missilesControl.h"

// класс башни
class Tower
{
private:
	// тип башни
	int m_type;
	// урон башни
	int m_dmg;
	// координаты башни на поле
	std::pair<int, int> m_position{ -1,-1 };
public:
	Tower(int i, int j, int type);
	~Tower() {}

	// отрисовка башни
	void drawTower(sf::RenderWindow & window);
	// выстрел
	void shoot(Field &field, Missiles &missiles);
};