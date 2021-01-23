#include "enemiesWave.h"

#include "enemy.h"
#include "roadCell.h"

EnemiesWave::EnemiesWave(int level, int maxLevel)
	: m_level{ level }, m_maxLevel{ maxLevel }
{
	m_enemiesList.reserve(25);
	// ��������� � ���������� �������� ������
	for (int i = 1; i < ENEMIES_COUNT; ++i) {
		sf::Texture *enemyTexture{ new sf::Texture() };
		(*enemyTexture).loadFromFile("images/enemies/enemy" + std::to_string(i) + ".png");
		m_enemiesTextures[i] = enemyTexture;
	}
}

EnemiesWave::~EnemiesWave()
{
	for (auto & var : m_enemiesTextures) {
		if (var) {
			delete var;
		}
	}
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
	// ������� ������� ������
	for (auto & var : m_enemiesList) {
		delete var;
	}
	m_enemiesList.clear();
}

void EnemiesWave::nextWave()
{
	// ���� ��� ���� ������� �����
	if (m_level != 5) {
		++m_level;
		// � ����������� �� ������ ����� � ��� ����� ������ ���������� � ������ ���-��
		switch (m_level)
		{
		case 1:
			m_enemiesLeft = 10;
			for (int i = 0; i < 10; ++i) {
				Enemy *enemy = new Enemy(1, m_enemiesTextures);
				m_enemiesList.push_back(enemy);
			}
			break;
		case 2:
			m_enemiesLeft = 10;
			for (int i = 0; i < 5; ++i) {
				Enemy *enemy = new Enemy(1, m_enemiesTextures);
				m_enemiesList.push_back(enemy);
			}
			for (int i = 0; i < 5; ++i) {
				Enemy *enemy = new Enemy(2, m_enemiesTextures);
				m_enemiesList.push_back(enemy);
			}
			break;
		case 3:
			m_enemiesLeft = 10;
			for (int i = 0; i < 5; ++i) {
				Enemy *enemy = new Enemy(2, m_enemiesTextures);
				m_enemiesList.push_back(enemy);
			}
			for (int i = 0; i < 5; ++i) {
				Enemy *enemy = new Enemy(3, m_enemiesTextures);
				m_enemiesList.push_back(enemy);
			}
			break;
		case 4:
			m_enemiesLeft = 15;
			for (int i = 0; i < 10; ++i) {
				Enemy *enemy = new Enemy(3, m_enemiesTextures);
				m_enemiesList.push_back(enemy);
			}
			for (int i = 0; i < 5; ++i) {
				Enemy *enemy = new Enemy(4, m_enemiesTextures);
				m_enemiesList.push_back(enemy);
			}
			break;
		case 5:
			m_enemiesLeft = 20;
			for (int i = 0; i < 5; ++i) {
				Enemy *enemy = new Enemy(3, m_enemiesTextures);
				m_enemiesList.push_back(enemy);
			}
			for (int i = 0; i < 15; ++i) {
				Enemy *enemy = new Enemy(4, m_enemiesTextures);
				m_enemiesList.push_back(enemy);
			}
			break;
		default:
			break;
		}
	}
}

void EnemiesWave::drawAllEnemies(sf::RenderWindow & window)
{
	for (auto & var : m_enemiesList) {
		// ���� ���� ���
		if (var->getIsAlive()) {
			var->drawEnemy(window);
			var->drawHPBar(window);
		}
	}
}

bool EnemiesWave::moveAllEnemies()
{
	for (auto & var : m_enemiesList) {
		// ���� ���� ���
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

void EnemiesWave::checkAlive(int &money)
{
	// �����������  ������� �����?
	bool f{ 0 };
	// ������� �����?
	bool erased{ 0 };
	auto var = m_enemiesList.begin();
	while (!f) {
		erased = 0;
		for (var = m_enemiesList.begin(); var != m_enemiesList.end(); ++var) {
			// ���� ���� ���
			if ((*var)->getIsAlive()) {
				if ((*var)->getHealth() <= 0) {
					money += (*var)->getCoins();
					erased = 1;
					// �������������, ��� ���� �����
					(*var)->setIsAlive(0);
					(*var)->setIsKilled(1);
					// ������� ����� � ������
					(*var)->getPositionEnemy()->removeEnemyFromCell(*var);
					--m_enemiesLeft;
					break;
				}
			}
		}
		// ���� �� ������� �����
		if (!erased) {
			// ���� ������ ���� ������ � ��� ��������� ����
			if (var == m_enemiesList.end()) {
				f = 1;
			}
		}
	}
}
