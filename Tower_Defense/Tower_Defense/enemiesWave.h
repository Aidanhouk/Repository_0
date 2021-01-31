#pragma once

#include <SFML/Graphics.hpp>

#include "consts.h"

class Enemy;
class RoadCell;
class LastEnemy;

// класс, управляющий волной противников
class EnemiesWave
{
private:
	// макс уровень волны
	const int m_maxWave;
	// указатель на последнего врага
	LastEnemy * lastEnemy{ nullptr };
	// уровень волны
	int m_waveLevel;
	// осталось монстров
	int m_enemiesLeft;
	// все монстры в волне
	std::vector<Enemy*> m_enemiesList;
	// тектуры врагов
	sf::Texture* m_enemiesTextures[ENEMIES_COUNT]{ nullptr };
public:
	// принимает уровень, с которого начнется игра и последний уровень волны
	EnemiesWave(int startWave, int maxWave);
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

	int getLevel() const { return m_waveLevel; }
	int getMaxLevel() const { return m_maxWave; }
	int getEnemiesLeft() const { return m_enemiesLeft; }
};