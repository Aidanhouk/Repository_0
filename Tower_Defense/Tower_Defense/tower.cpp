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

Tower::Tower(int i, int j, int type, sf::Texture * towersTextures[TOWERS_COUNT], sf::Texture * buffTextures[4])
	: m_type{ type }, m_dmg{ TOWERS_DAMAGE[type] * (1 + 2 * gameSpeed) }, m_towerTexture{ towersTextures[type] }
{
	m_position.first = i;
	m_position.second = j;

	if (type > 6) {
		m_range = 2;
	}

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

	for (int q = 0; q < 4; ++q) {
		m_buffTextures[q] = buffTextures[q];
	}
}

void Tower::drawTower()
{
	// отрисовка башни
	sf::Sprite tower(*m_towerTexture);
	tower.setPosition(W * m_position.second, W * m_position.first);
	(*window).draw(tower);
	// отрисовка бафов у башни
	if (m_damageTowers > 0) {
		// символ прицела
		sf::Sprite damageAim(*m_buffTextures[0]);
		damageAim.setPosition(tower.getPosition().x + 4, tower.getPosition().y + 4);
		(*window).draw(damageAim);
		// стрелочки
		sf::Sprite damagePtr1(*m_buffTextures[1]);
		sf::Sprite damagePtr2(*m_buffTextures[1]);
		sf::Sprite damagePtr3(*m_buffTextures[1]);
		switch (m_damageTowers)
		{
		case 1:
			damagePtr1.setPosition(tower.getPosition().x + 4 + 35, tower.getPosition().y + 4);
			(*window).draw(damagePtr1);
			break;
		case 2:
			damagePtr1.setPosition(tower.getPosition().x + 4 + 35, tower.getPosition().y + 4);
			damagePtr2.setPosition(tower.getPosition().x + 4 + 35 + 10, tower.getPosition().y + 4);
			(*window).draw(damagePtr1);
			(*window).draw(damagePtr2);
			break;
		default:
			damagePtr1.setPosition(tower.getPosition().x + 4 + 35, tower.getPosition().y + 4);
			damagePtr2.setPosition(tower.getPosition().x + 4 + 35 + 10, tower.getPosition().y + 4);
			damagePtr3.setPosition(tower.getPosition().x + 4 + 35 + 20, tower.getPosition().y + 4);
			(*window).draw(damagePtr1);
			(*window).draw(damagePtr2);
			(*window).draw(damagePtr3);
			break;
		}
	}
	if (m_range > 1 && m_type <= 6) {
		// символ range
		sf::Sprite range(*m_buffTextures[2]);
		range.setPosition(tower.getPosition().x, tower.getPosition().y + (W >> 1));
		(*window).draw(range);
		// стрелочки
		sf::Sprite rangePtr1(*m_buffTextures[3]);
		sf::Sprite rangePtr2(*m_buffTextures[3]);
		sf::Sprite rangePtr3(*m_buffTextures[3]);
		switch (m_range)
		{
		case 2:
			rangePtr1.setPosition(tower.getPosition().x + 4 + 35, tower.getPosition().y + 4 + (W >> 1));
			(*window).draw(rangePtr1);
			break;
		case 3:
			rangePtr1.setPosition(tower.getPosition().x + 4 + 35, tower.getPosition().y + 4 + (W >> 1));
			rangePtr2.setPosition(tower.getPosition().x + 4 + 35 + 10, tower.getPosition().y + 4 + (W >> 1));
			(*window).draw(rangePtr1);
			(*window).draw(rangePtr2);
			break;
		default:
			rangePtr1.setPosition(tower.getPosition().x + 4 + 35, tower.getPosition().y + 4 + (W >> 1));
			rangePtr2.setPosition(tower.getPosition().x + 4 + 35 + 10, tower.getPosition().y + 4 + (W >> 1));
			rangePtr3.setPosition(tower.getPosition().x + 4 + 35 + 20, tower.getPosition().y + 4 + (W >> 1));
			(*window).draw(rangePtr1);
			(*window).draw(rangePtr2);
			(*window).draw(rangePtr3);
			break;
		}
	}
}

void Tower::shoot(Missiles &missiles)
{
	int count{ 0 };
	for (auto cellToAttack = m_cellsInRange.begin(); cellToAttack != m_cellsInRange.end(); ++cellToAttack) {
		if (!(*cellToAttack)->isCellClear()) {
			for (auto & enemy : (*cellToAttack)->getEnemiesOnCell()) {
				// наносится урон и если враг не убит, то создается объект снаряда
				if (!(enemy->getDamage(m_dmg))) {
					// создаем объект снаряда и добавляем его в вектор снарядов
					std::pair<Tower*, Enemy*> *missile{ new std::pair<Tower*, Enemy*> };
					missile->first = this;
					missile->second = enemy;
					missiles.addMissile(missile);
					++count;
					// если башня 4 типа, то она стреляет по 3 врагам одновременно
					if (m_type != 4 || count == 3) {
						return;
					}
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
	m_damageTowers = 0;
	float newDamage{ 1 };
	int newRange{ 1 };
	for (int i = m_position.first - 2; i <= m_position.first + 2; ++i) {
		if (i <= -1 || i >= ROWS) { continue; }
		for (int j = m_position.second - 2; j <= m_position.second + 2; ++j) {
			if (j <= -1 || j >= COLS) { continue; }
			if ((*field).getTowerOnCell(i, j)) {
				switch ((*field).getTowerOnCell(i, j)->getTowerType())
				{
				case 7:
					newDamage += 0.3f;
					++m_damageTowers;
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
	m_dmg = TOWERS_DAMAGE[m_type] * (1 + 2 * gameSpeed) * newDamage;
	// если радиус поменялся, то определяем, по каким клеткам может стрелять башня
	if (newRange != m_range) {
		m_range = newRange;
		changeRange();
	}
}