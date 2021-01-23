#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "consts.h"

class Enemy;
class RoadCell;

// класс, управляющий волной противников
class EnemiesWave
{
private:
	// уровень волны
	int m_level;
	// макс уровень волны
	const int m_maxLevel;
	// осталось монстров
	int m_enemiesLeft;
	// все монстры в волне
	std::vector<Enemy*> m_enemiesList;
	// тектуры врагов
	sf::Texture* m_enemiesTextures[ENEMIES_COUNT]{ nullptr };
public:
	// принимает число - уровень волны
	EnemiesWave(int level, int maxLevel);
	~EnemiesWave();

	// выпустить следующего монстра
	void spawnNextEnemy(RoadCell * cellToSpawn);
	// очищает врагов из волны
	void cleanWave();
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
	// возвращает макс уровень волны
	int getMaxLevel() const { return m_maxLevel; }
	// возвращает кол-во врагов в волне
	int getEnemiesLeft() const { return m_enemiesLeft; }
};