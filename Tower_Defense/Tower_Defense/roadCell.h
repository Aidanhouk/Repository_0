#pragma once

#include <utility>
#include <vector>
class Enemy;

// ����� ������ ������
class RoadCell
{
private:
	// ������� ������ �� ����
	std::pair<int, int> m_posOnField;
	// ��������� �� ��������� ������ ������
	RoadCell *m_nextCell;
	// ��������� �� ����������� ������ ������
	RoadCell *m_prevCell;
	// ��� ����� ������� ������ � ����������� �� ������ ����������� �� ���� ������,
	// �� � ���� ������ ���� �� 1 ������ ����� ������ ������ 1 ����
	std::vector<Enemy*> m_enemiesOnCell;
	//Enemy *m_enemyOnCell{ nullptr };
	// ���-�� ������ �� ���� ����
	int m_countEnemiesOnCell;
public:
	// ��������� ������� �� ���� � ��������� �� ���� ������
	RoadCell(int i, int j, RoadCell * nextCell = nullptr);
	// ����������� ������ � ���� ������
	~RoadCell() { delete m_nextCell; }

	// ���������� ������� ������ �� ����
	std::pair<int, int> &getCoordinates() { return m_posOnField; }

	// ���������� m_nextCell
	RoadCell *getNextCell() { return m_nextCell; }
	// ���������� m_nextCell
	void setNextCell(RoadCell * nextCell) { m_nextCell = nextCell; }
	
	// ���������� m_prevCell
	RoadCell *getPrevCell() { return m_prevCell; }
	// ���������� m_prevCell
	void setPrevCell(RoadCell * prevCell) { m_prevCell = prevCell; }
	
	// ��������� ����� �� ���� ������, ������� ������ �� ��� ����� ����
	Enemy * getEnemyOnCell();
	// �������� ����� �� ��� ������
	void setEnemyOnCell(Enemy * enemy) { m_enemiesOnCell.push_back(enemy); }
	// ������� ����� �� ������
	void removeEnemyFromCell(Enemy * enemy);
};