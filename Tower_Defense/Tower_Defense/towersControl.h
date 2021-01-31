#pragma once

#include <SFML/Graphics.hpp>

#include "consts.h"

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
	// текстуры бафов
	sf::Texture* m_buffsTextures[4];
public:
	TowersControl();
	~TowersControl();

	// поставить башню
	void addTower(int i, int j, int type);
	// отрисовать все башни
	void drawAllTowers();
	// башни стреляют
	void towersShoot(Missiles &missiles);
	// отметить выбранную башню для удаления
	void markTowerToDelete(int i, int j);
	// удалить башню с поля + вернуть половину ее стоимости
	int deleteTower(int i, int j);
	// изменить урон башен
	void changeTowersDamage();
	// проверить, есть ли рядом башни-бафы
	void checkTowersForBuffs();
};