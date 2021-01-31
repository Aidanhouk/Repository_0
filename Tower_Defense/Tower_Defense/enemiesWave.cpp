#include "enemiesWave.h"

#include "globals.h"
#include "enemy.h"
#include "roadCell.h"
#include "lastEnemy.h"

EnemiesWave::EnemiesWave(int startWave, int maxWave)
	: m_waveLevel{ startWave - 1 }, m_maxWave{ maxWave }
{
	m_enemiesList.reserve(30);
	// скачиваем и записываем текстуры врагов
	for (int i = 1; i < ENEMIES_COUNT; ++i) {
		m_enemiesTextures[i] = new sf::Texture();
		(*m_enemiesTextures[i]).loadFromFile("images/enemies/enemy" + std::to_string(i) + ".png");
	}
}

EnemiesWave::~EnemiesWave()
{
	cleanWave();
	for (auto & var : m_enemiesTextures) {
		if (var) {
			delete var;
		}
	}
}

void EnemiesWave::spawnNextEnemy(RoadCell * cellToSpawn)
{
	for (auto & var : m_enemiesList) {
		// если враг еще не заспавнился
		if (!var->getPositionEnemy() && !var->getIsKilled()) {
			var->setPosition(cellToSpawn);
			var->setDirection(cellToSpawn);
			var->setIsAlive(1);
			break;
		}
	}
}

void EnemiesWave::cleanWave()
{
	if (lastEnemy) {
		lastEnemy->deleteEffects();
		delete lastEnemy;
		lastEnemy = nullptr;
	}
	for (auto & var : m_enemiesList) {
		delete var;
	}
	m_enemiesList.clear();
}

void EnemiesWave::drawAllEnemies()
{
	for (auto & var : m_enemiesList) {
		if (var->getIsAlive()) {
			var->drawEnemy();
			var->drawHPBar();
		}
	}
}

bool EnemiesWave::moveAllEnemies()
{
	for (auto & var : m_enemiesList) {
		if (var->getIsAlive()) {
			var->enemyMoves();
			// если враг прошел полную клетку
			if (var->getDistance() >= W) {
				var->changePosition();
				// если враг еще не закончил путь и есть куда двигаться дальше
				if (var->getPositionEnemy()->getNextCell()) {
					var->setDirection(var->getPositionEnemy());
				}
				else {
					return 1;
				}
			}
		}
	}
	return 0;
}

void EnemiesWave::changeEnemiesSpeed()
{
	for (auto & var : m_enemiesList) {
		if (!var->getIsKilled()) {
			var->changeSpeed();
		}
	}
}

void EnemiesWave::changeEnemiesDamage()
{
	for (auto & var : m_enemiesList) {
		if (!var->getIsKilled()) {
			var->changeDamage();
		}
	}
}

void EnemiesWave::drawLastEnemyEffects()
{
	if (lastEnemy) {
		if (!pause) {
			lastEnemy->moveEffects();
		}
		lastEnemy->drawEffects();
	}
	else {
		for (auto & var : m_enemiesList) {
			if (var->getIsAlive()) {
				lastEnemy = new LastEnemy(var);
				lastEnemy->createEffects();
			}
		}
	}
}
