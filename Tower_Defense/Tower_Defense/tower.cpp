#include "tower.h"

#include "globals.h"
#include "field.h"
#include "missiles.h"
#include "enemy.h"
#include "roadCell.h"

void Tower::changeRange()
{
	m_cellsInRange.clear();
	// проходимся по всей дороге с конца, чтобы найти клетки, по которым может стрелять башня
	for (auto currentCell = (*field).getFinishPos(); currentCell != (*field).getStartPos(); currentCell = currentCell->getPrevCell()) {
		// переменные для вычисления дистанции между клеткой и башней
		std::pair<int, int> cellCoord{ currentCell->getCoordinates() };
		std::pair<int, int> coordDif{ cellCoord.first - m_position.first, cellCoord.second - m_position.second };
		if (coordDif.first <= m_range && coordDif.first >= -m_range && coordDif.second <= m_range && coordDif.second >= -m_range) {
			m_cellsInRange.push_back(currentCell);
		}
	}
}

Tower::Tower(int i, int j, int type, sf::Texture * towersTextures[TOWERS_COUNT])
	: m_type{ type }, m_dmg{ TOWERS_DAMAGE[type] * (1 + 2 * gameSpeed) }, m_towerTexture{ towersTextures[type] }
{
	m_position.first = i;
	m_position.second = j;

	m_cellsInRange.reserve(12);
	// проходимся по всей дороге с конца, чтобы найти клетки, по которым может стрелять башня
	for (auto currentCell = (*field).getFinishPos(); currentCell != (*field).getStartPos(); currentCell = currentCell->getPrevCell()) {
		// переменные для вычисления дистанции между клеткой и башней
		std::pair<int, int> cellCoord{ currentCell->getCoordinates() };
		std::pair<int, int> coordDif{ cellCoord.first - i, cellCoord.second - j };
		// если клетка находится вокруг башни (8 клеток)
		if (coordDif.first <= 1 && coordDif.first >= -1 && coordDif.second <= 1 && coordDif.second >= -1) {
			m_cellsInRange.push_back(currentCell);
		}
	}
}

void Tower::drawTower()
{
	sf::Sprite tower(*m_towerTexture);
	tower.setPosition(W * m_position.second, W * m_position.first);
	(*window).draw(tower);
}

void Tower::shoot(Missiles &missiles)
{
	int count{ 0 };
	for (auto cellToAttack = m_cellsInRange.begin(); cellToAttack != m_cellsInRange.end(); ++cellToAttack) {
		if ((*cellToAttack)->getEnemyOnCell()) {
			// наносится урон и если враг не убит, то создается объект снаряда
			if (!(*cellToAttack)->getEnemyOnCell()->getDamage(m_dmg)) {
				// создаем объект снаряда и добавляем его в вектор снарядов
				std::pair<Tower*, Enemy*> *missile{ new std::pair<Tower*, Enemy*> };
				missile->first = this;
				missile->second = (*cellToAttack)->getEnemyOnCell();
				missiles.addMissile(missile);
				++count;
				if (m_type != 4 || count == 3) {
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

void Tower::checkForBuffs()
{
	int newDamage{ 1 };
	int newRange{ 1 };
	for (int i = m_position.first - 1; i <= m_position.first + 1; ++i) {
		if (i == -1 || i == ROWS) { continue; }
		for (int j = m_position.second - 1; j <= m_position.second + 1; ++j) {
			if (j == -1 || j == COLS) { continue; }
			if ((*field).getTowerOnCell(i, j)) {
				switch ((*field).getTowerOnCell(i, j)->getTowerType())
				{
				case 7:
					++newDamage;
					break;
				case 8:
					++newRange;
					break;
				default:
					break;
				}
			}
		}
	}
	m_dmg = newDamage * TOWERS_DAMAGE[m_type] * (1 + 2 * gameSpeed);
	// если радиус поменялся, то определяем, по каким клеткам может стрелять башня
	if (newRange != m_range) {
		m_range = newRange;
		changeRange();
	}
}