#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "consts.h"

class Field;
class Missiles;
class Tower;

// класс, контролирующий все башни
class TowersControl
{
private:
	// все башни
	std::vector<Tower*> m_towersList;
	// тектуры башен
	sf::Texture* m_towersTextures[TOWERS_COUNT]{ nullptr };
public:
	TowersControl();
	~TowersControl();

	// поставить башню
	void addTower(int i, int j, int type);
	// отрисовать все башни
	void drawAllTowers(sf::RenderWindow &window);
	// башни стреляют
	void towersShoot(Field & field, Missiles &missiles);
};