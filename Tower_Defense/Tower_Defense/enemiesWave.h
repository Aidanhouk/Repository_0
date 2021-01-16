#pragma once

#include <vector>

#include "enemy.h"
#include "roadCell.h"

// класс, управляющий волной противников
class EnemiesWave
{
private:
	// уровень волны
	int m_level;
	// осталось монстров
	int m_enemiesLeft;
	// все монстры в волне
	std::vector<Enemy*> m_enemiesList;
public:
	// принимает число - уровень волны
	EnemiesWave(int level);
	~EnemiesWave() {};

	// выпустить следующего монстра
	void spawnNextEnemy(RoadCell * cellToSpawn);
	// создаем след волну
	void nextWave();
	// отрисовка всех врагов
	void drawAllEnemies(sf::RenderWindow &window);
	// движение врагов, если возвращает 1, то игрок проиграл
	bool moveAllEnemies();
	// проверить, живы ли враги
	void checkAlive(int &money);

	// возвращает уровень волны
	int getLevel() const { return m_level; }
	// возвращает кол-во врагов в волне
	int getEnemiesLeft() const { return m_enemiesLeft; }
};