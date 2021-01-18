#include "tower.h"

#include "consts.h"
#include "enemy.h"

Tower::Tower(int i, int j, int type)
	: m_type{ type }
{
	m_position.first = i;
	m_position.second = j;
	m_dmg = TOWERS_DAMAGE[type];
}

void Tower::drawTower(sf::RenderWindow & window)
{
	sf::CircleShape tower(25, 10);
	tower.setPosition((float)(W) * m_position.second + 15, (float)(W) * m_position.first + 15);
	switch (m_type)
	{
	case 1:
		tower.setFillColor(sf::Color(115, 190, 250));
		break;
	case 2:
		tower.setFillColor(sf::Color(240, 85, 85));
		break;
	case 3:
		tower.setFillColor(sf::Color(210, 40, 255));
		break;
	}
	window.draw(tower);
}

void Tower::shoot(Field & field, Missiles &missiles)
{
	// проходимся по всей дороге с конца
	for (auto currentCell = field.getFinishPos(); currentCell != field.getStartPos(); currentCell = currentCell->getPrevCell()) {
		// если на этой ячейке есть враг
		if (currentCell->getEnemyOnCell()) {
			// переменные для вычисления дистанции между клеткой и башней
			std::pair<int, int> enemyCellCoord{ currentCell->getCoordinates() };
			std::pair<int, int> coordDif{ enemyCellCoord.first - m_position.first, enemyCellCoord.second - m_position.second };
			// если враг находится вокруг башни (8 клеток)
			if (coordDif.first <= 1 && coordDif.first >= -1 && coordDif.second <= 1 && coordDif.second >= -1) {
				currentCell->getEnemyOnCell()->getDamage(m_dmg);
				// создаем объект снаряда и добавляем его в вектор снарядов
				std::pair<std::pair<int, int>, Enemy*> *missile{ new std::pair<std::pair<int, int>, Enemy*> };
				missile->first.first = m_position.first;
				missile->first.second = m_position.second;
				missile->second = currentCell->getEnemyOnCell();
				missiles.addMissile(missile);
				break;
			}

		}
	}
}
