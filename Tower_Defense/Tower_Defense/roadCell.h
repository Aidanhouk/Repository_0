#pragma once

#include <utility>
class Enemy;

// ����� ������ ������
class RoadCell
{
private:
	// ������� ������ �� ����
	std::pair<int, int> m_posOnField;
	// ��������� �� ��������� ������ ������
	RoadCell *m_nextCell;
	// ��� ����� ������� ������ � ����������� �� ������ ����������� �� ���� ������,
	// �� � ���� ������ ���� �� 1 ������ ����� ������ ������ 1 ����
	Enemy *m_enemyOnCell{ nullptr };
	// ���-�� ������ �� ���� ����
	int m_countEnemiesOnCell;
public:
	// ��������� ������� �� ���� � ��������� �� ���� ������
	RoadCell(int i, int j, RoadCell * nextCell = nullptr);
	// ����������� ������ ��� ���� ������
	~RoadCell() { delete m_nextCell; }

	// ���������� ������� ������ �� ����
	std::pair<int, int> &getCoordinates() { return m_posOnField; }
	// ���������� m_nextCell
	RoadCell *getNextCell() { return m_nextCell; }
	// ���������� m_nextCell
	void setNextCell(RoadCell * nextCell) { m_nextCell = nextCell; }
	// ��������� ����� �� ���� ������
	Enemy * getEnemyOnCell() { return m_enemyOnCell; }
	// ���������� ����� �� ��� ������
	void setEnemyOnCell(Enemy * enemy) { m_enemyOnCell = enemy; }
};