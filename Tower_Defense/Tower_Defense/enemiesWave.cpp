#include "enemiesWave.h"

#include "globals.h"
#include "enemy.h"
#include "roadCell.h"
#include "lastEnemy.h"

EnemiesWave::EnemiesWave(int level, int maxLevel)
	: m_level{ level - 1 }, m_maxLevel{ maxLevel }
{
	m_enemiesList.reserve(50);
	// ��������� � ���������� �������� ������
	for (int i = 1; i < ENEMIES_COUNT; ++i) {
		m_enemiesTextures[i] = new sf::Texture();
		(*m_enemiesTextures[i]).loadFromFile("images/enemies/enemy" + std::to_string(i) + ".png");
	}

	m_enemiesTextures[0] = new sf::Texture();
	(*m_enemiesTextures[0]).loadFromFile("images/enemies/enemy0.png");
}

EnemiesWave::~EnemiesWave()
{
	for (auto & var : m_enemiesTextures) {
		if (var) {
			delete var;
		}
	}
	cleanWave();
}

void EnemiesWave::spawnNextEnemy(RoadCell * cellToSpawn)
{
	for (auto & var : m_enemiesList) {
		// ���� ���� ��� �� �����������
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
			// ���� ���� ������ ������ ������
			if (var->getDistance() >= W) {
				var->changePosition();
				// ���� ���� ��� �� �������� ���� � ���� ���� ��������� ������
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
