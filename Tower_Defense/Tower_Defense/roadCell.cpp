#include "roadCell.h"

RoadCell::RoadCell(int i, int j, RoadCell * nextCell)
	:m_nextCell{ nextCell }
{
	m_posOnField.first = i;
	m_posOnField.second = j;
}

Enemy * RoadCell::getEnemyOnCell()
{
	if (!m_enemiesOnCell.empty()) {
		return m_enemiesOnCell.front();
	}
	return nullptr;
}

void RoadCell::removeEnemyFromCell(Enemy * enemy)
{
	if (m_enemiesOnCell.empty()) { return; }
	auto enemyIter{ std::find(m_enemiesOnCell.begin(), m_enemiesOnCell.end(), enemy) };
	if (enemyIter != m_enemiesOnCell.end()) {
		m_enemiesOnCell.erase(enemyIter);
	}
}