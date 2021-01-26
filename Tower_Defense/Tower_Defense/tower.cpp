#include "tower.h"

#include "globals.h"
#include "field.h"
#include "missiles.h"
#include "enemy.h"
#include "roadCell.h"

Tower::Tower(int i, int j, int type, sf::Texture * towersTextures[TOWERS_COUNT])
	: m_type{ type }, m_dmg{ TOWERS_DAMAGE[type] * (1 + 2 * gameSpeed) }, m_towerTexture{ towersTextures[type] }
{
	m_position.first = i;
	m_position.second = j;
}

void Tower::drawTower(sf::RenderWindow & window)
{
	sf::Sprite tower(*m_towerTexture);
	tower.setPosition(W * m_position.second, W * m_position.first);
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
				// наносится урон и если враг убит..
				if (!currentCell->getEnemyOnCell()->getDamage(m_dmg)) {
					// создаем объект снаряда и добавляем его в вектор снарядов
					std::pair<Tower*, Enemy*> *missile{ new std::pair<Tower*, Enemy*> };
					missile->first = this;
					missile->second = currentCell->getEnemyOnCell();
					missiles.addMissile(missile);
					break;
				}
			}

		}
	}
}

void Tower::changeDamage()
{
	if (gameSpeed) {
		m_dmg *= 3;
	}
	else {
		m_dmg /= 3;
	}
}
