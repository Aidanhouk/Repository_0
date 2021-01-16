#pragma once

#include <vector>

#include "tower.h"
class Field;
class Missiles;

// класс, контролирующий все башни
class TowersControl
{
private:
	// все башни
	std::vector<Tower*> m_towersList;
public:
	TowersControl() {}
	~TowersControl();

	// поставить башню
	void addTower(int i, int j, int type);
	// отрисовать все башни
	void drawAllTowers(sf::RenderWindow &window);
	// башни стреляют
	void towersShoot(Field & field, Missiles &missiles);
};