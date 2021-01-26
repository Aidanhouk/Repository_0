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
	// ���������� �� ���� ������ � �����
	for (auto currentCell = field.getFinishPos(); currentCell != field.getStartPos(); currentCell = currentCell->getPrevCell()) {
		// ���� �� ���� ������ ���� ����
		if (currentCell->getEnemyOnCell()) {
			// ���������� ��� ���������� ��������� ����� ������� � ������
			std::pair<int, int> enemyCellCoord{ currentCell->getCoordinates() };
			std::pair<int, int> coordDif{ enemyCellCoord.first - m_position.first, enemyCellCoord.second - m_position.second };
			// ���� ���� ��������� ������ ����� (8 ������)
			if (coordDif.first <= 1 && coordDif.first >= -1 && coordDif.second <= 1 && coordDif.second >= -1) {
				// ��������� ���� � ���� ���� ����..
				if (!currentCell->getEnemyOnCell()->getDamage(m_dmg)) {
					// ������� ������ ������� � ��������� ��� � ������ ��������
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
