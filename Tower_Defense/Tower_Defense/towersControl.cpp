#include "towersControl.h"

#include "missiles.h"
#include "tower.h"

TowersControl::TowersControl()
{
	// скачиваем и записываем текстуры башен
	for (int i = 1; i < TOWERS_COUNT; ++i) {
		sf::Texture *tower{ new sf::Texture() };
		(*tower).loadFromFile("images/towers/tower" + std::to_string(i) + ".png");
		m_towersTextures[i] = tower;
	}
}

TowersControl::~TowersControl()
{
	for (auto & var : m_towersList) {
		delete var;
	}
	for (auto var : m_towersTextures) {
		if (var) {
			delete var;
		}
	}
}

void TowersControl::addTower(int i, int j, int type)
{
	Tower *tower = new Tower(i, j, type, m_towersTextures);
	m_towersList.push_back(tower);
}

void TowersControl::drawAllTowers(sf::RenderWindow & window)
{
	for (auto & var : m_towersList) {
		var->drawTower(window);
	}
}

void TowersControl::towersShoot(Field & field, Missiles &missiles, int &money)
{
	// удаляем старые выстрелы
	missiles.deleteMissiles();
	for (auto & var : m_towersList) {
		var->shoot(field, missiles, money);
	}
}
