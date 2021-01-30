#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "consts.h"

class Enemy;
class RoadCell;
class LastEnemy;

// класс, управляющий волной противников
class EnemiesWave
{
private:
	// макс уровень волны
	const int m_maxLevel;
	// указатель на последнего врага
	LastEnemy * lastEnemy{ nullptr };
	// уровень волны
	int m_level;
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
	void drawAllEnemies();
	// движение врагов, если возвращает 1, то игрок проиграл
	bool moveAllEnemies();
	// уменьшить колв-во противников на 1
	void reduceEnemiesLeft() { --m_enemiesLeft; }
	// изменить скорость передвижения врагов
	void changeEnemiesSpeed();
	// изменить урон врагов
	void changeEnemiesDamage();
	// отрисовывать эффекты в конце волны
	void drawLastEnemyEffects();

	int getLevel() const { return m_level; }
	int getMaxLevel() const { return m_maxLevel; }
	int getEnemiesLeft() const { return m_enemiesLeft; }
};