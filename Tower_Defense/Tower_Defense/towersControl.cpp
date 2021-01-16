#include "towersControl.h"

#include "consts.h"

TowersControl::~TowersControl()
{
	for (auto & var : m_towersList) {
		delete var;
	}
}

void TowersControl::addTower(int i, int j, int type)
{
	Tower *tower = new Tower(i, j, type);
	m_towersList.push_back(tower);
}

void TowersControl::drawAllTowers(sf::RenderWindow & window)
{
	for (auto & var : m_towersList) {
		var->drawTower(window);
	}
}

void TowersControl::towersShoot(Field & field, Missiles &missiles)
{
	for (auto & var : m_towersList) {
		var->shoot(field, missiles);
	}
}
