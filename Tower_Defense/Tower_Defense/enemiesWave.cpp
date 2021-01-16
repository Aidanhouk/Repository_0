#include "enemiesWave.h"

#include "consts.h"

EnemiesWave::EnemiesWave(int level)
	: m_level{ level } {}

void EnemiesWave::spawnNextEnemy(RoadCell * cellToSpawn)
{
	for (auto & var : m_enemiesList) {
		// если враг еще не заспавнился
		if (!var->getPositionEnemy()) {
			var->setPosition(cellToSpawn);
			var->setDirection(cellToSpawn);
			break;
		}
	}
}

void EnemiesWave::nextWave()
{
	// если уже макс уровень волны
	if (m_level != 5) {
		++m_level;
	}
	m_enemiesList.clear();
	// в зависимости от уровня волны в ней будут разные противники в разном кол-ве
	switch (m_level)
	{
	case 1:
		m_enemiesLeft = 5;
		m_enemiesList.reserve(m_enemiesLeft);
		for (int i = 0; i < 5; ++i) {
			Enemy *enemy = new Enemy(1);
			m_enemiesList.push_back(enemy);
		}
		break;
	case 2:
		m_enemiesLeft = 10;
		m_enemiesList.reserve(m_enemiesLeft);
		for (int i = 0; i < 5; ++i) {
			Enemy *enemy = new Enemy(1);
			m_enemiesList.push_back(enemy);
		}
		for (int i = 0; i < 5; ++i) {
			Enemy *enemy = new Enemy(2);
			m_enemiesList.push_back(enemy);
		}
		break;
	case 3:
		m_enemiesLeft = 10;
		m_enemiesList.reserve(m_enemiesLeft);
		for (int i = 0; i < 5; ++i) {
			Enemy *enemy = new Enemy(2);
			m_enemiesList.push_back(enemy);
		}
		for (int i = 0; i < 5; ++i) {
			Enemy *enemy = new Enemy(3);
			m_enemiesList.push_back(enemy);
		}
		break;
	case 4:
		m_enemiesLeft = 10;
		m_enemiesList.reserve(m_enemiesLeft);
		for (int i = 0; i < 10; ++i) {
			Enemy *enemy = new Enemy(3);
			m_enemiesList.push_back(enemy);
		}
		break;
	case 5:
		m_enemiesLeft = 10;
		m_enemiesList.reserve(m_enemiesLeft);
		for (int i = 0; i < 10; ++i) {
			Enemy *enemy = new Enemy(4);
			m_enemiesList.push_back(enemy);
		}
		break;
	default:
		break;
	}
}

void EnemiesWave::drawAllEnemies(sf::RenderWindow & window)
{
	for (auto & var : m_enemiesList) {
		// если враг уже заспавнился
		if (var->getPositionEnemy()) {
			var->drawEnemy(window);
		}
		else {
			break;
		}
	}
}

bool EnemiesWave::moveAllEnemies()
{
	for (auto & var : m_enemiesList) {
		// если враг уже заспавнился
		if (var->getPositionEnemy()) {
			var->enemyMoves();
			// если враг прошел полную клетку
			if (var->getDistance() == W) {
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
		else {
			break;
		}
	}
	return 0;
}

void EnemiesWave::checkAlive(int &money)
{
	// закончились  мертвые враги?
	bool f{ 0 };
	// удалили врага?
	bool erased{ 0 };
	auto var = m_enemiesList.begin();
	while (!f) {
		erased = 0;
		for (var = m_enemiesList.begin(); var != m_enemiesList.end(); ++var) {
			// если враг уже заспавнился
			if ((*var)->getPositionEnemy()) {
				if ((*var)->getHealth() <= 0) {
					money += (*var)->getCoins();
					erased = 1;
					// убираем врага с клетки
					(*var)->getPositionEnemy()->setEnemyOnCell(nullptr);
					// освобождаем память, выделенную для врага при создании волны
					delete (*var);
					// удаляем врага из текущей волны
					m_enemiesList.erase(var);
					--m_enemiesLeft;
					break;
				}
			}
			// если дошли до врага, который еще не появился
			else {
				f = 1;
				break;
			}
		}
		// если не удалили врага
		if (!erased) {
			// если прошли весь список и все оказались живы
			if (var == m_enemiesList.end()) {
				f = 1;
			}
		}
	}
}
