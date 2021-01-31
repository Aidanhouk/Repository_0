#include "towersControl.h"

#include "globals.h"
#include "missiles.h"
#include "tower.h"
#include "field.h"

TowersControl::TowersControl()
{
	// скачиваем и записываем текстуры башен
	for (int i = 1; i < TOWERS_COUNT; ++i) {
		sf::Texture *tower{ new sf::Texture() };
		(*tower).loadFromFile("images/towers/tower" + std::to_string(i) + ".png");
		m_towersTextures[i] = tower;
	}
	// скачиваем и записываем текстуры бафов
	for (int i = 0; i < 4; ++i) {
		sf::Texture *buffTexture{ new sf::Texture() };
		(*buffTexture).loadFromFile("images/buffs/buff" + std::to_string(i) + ".png");
		m_buffsTextures[i] = buffTexture;
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
	for (auto var : m_buffsTextures) {
		delete var;
	}
}

void TowersControl::addTower(int i, int j, int type)
{
	Tower *tower = new Tower(i, j, type, m_towersTextures, m_buffsTextures);
	m_towersList.push_back(tower);
	(*field).addTowerOnCell(i, j, tower);
}

void TowersControl::drawAllTowers()
{
	for (auto & var : m_towersList) {
		var->drawTower();
	}
}

void TowersControl::towersShoot(Missiles &missiles)
{
	// удаляем старые выстрелы
	missiles.deleteMissiles();
	for (auto & var : m_towersList) {
		if (var->getTowerType() > 6) { continue; }
		var->shoot(missiles);
	}
}

void TowersControl::markTowerToDelete(int i, int j)
{
	sf::RectangleShape cross1(sf::Vector2f(W * 1.29f, W / 10));
	cross1.setPosition(W * j + 8, W * i);
	cross1.rotate(45);
	cross1.setFillColor(sf::Color(150, 25, 25));
	(*window).draw(cross1);
	sf::RectangleShape cross2(sf::Vector2f(W * 1.29f, W / 10));
	cross2.setPosition(W * j + 2, W * (i + 1) - 6);
	cross2.rotate(-45);
	cross2.setFillColor(sf::Color(150, 25, 25));
	(*window).draw(cross2);
}

int TowersControl::deleteTower(int i, int j)
{
	for (auto it = m_towersList.begin(); it != m_towersList.end(); ++it) {
		if ((*it)->getPosition().first == i && (*it)->getPosition().second == j) {
			int towerPrice{ TOWERS_PRICE[(*it)->getTowerType()] };
			m_towersList.erase(it);
			return (towerPrice >> 1);
		}
	}
}

void TowersControl::changeTowersDamage()
{
	for (auto & var : m_towersList) {
		if (var->getTowerType() > 6) { continue; }
		var->changeDamage();
	}
}

void TowersControl::checkTowersForBuffs()
{
	for (auto & var : m_towersList) {
		if (var->getTowerType() > 6) { continue; }
		var->checkForBuffs();
	}
}
