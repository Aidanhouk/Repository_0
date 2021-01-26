#include "towersControl.h"

#include "missiles.h"
#include "tower.h"

TowersControl::TowersControl()
{
	// ��������� � ���������� �������� �����
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

void TowersControl::towersShoot(Field & field, Missiles &missiles)
{
	// ������� ������ ��������
	missiles.deleteMissiles();
	for (auto & var : m_towersList) {
		var->shoot(field, missiles);
	}
}

void TowersControl::markTowerToDelete(sf::RenderWindow & window, int i, int j)
{
	sf::RectangleShape cross1(sf::Vector2f(W * 1.29, W / 10));
	cross1.setPosition(W * j + 8, W * i);
	cross1.rotate(45);
	cross1.setFillColor(sf::Color(150, 25, 25));
	window.draw(cross1);
	sf::RectangleShape cross2(sf::Vector2f(W * 1.29, W / 10));
	cross2.setPosition(W * j + 2, W * (i + 1) - 6);
	cross2.rotate(-45);
	cross2.setFillColor(sf::Color(150, 25, 25));
	window.draw(cross2);
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
		var->changeDamage();
	}
}
