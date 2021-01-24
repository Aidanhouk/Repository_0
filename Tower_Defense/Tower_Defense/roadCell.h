#pragma once

#include <vector>

class Enemy;
class BlockOnField;

// ����� ������ ������
class RoadCell
{
private:
	// ������� ������ �� ���� <������, �������>
	std::pair<int, int> m_posOnField;
	// ��������� �� ��������� ������ ������
	RoadCell *m_nextCell;
	// ��������� �� ����������� ������ ������
	RoadCell *m_prevCell;
	// ��������� �� ����, ������� ��������� �� ���� ������
	BlockOnField *m_blockOnCell{ nullptr };
	// ������ � ����������� �� ������ ����������� �� ���� ������,
	std::vector<Enemy*> m_enemiesOnCell;
public:
	// ��������� ������� �� ���� � ��������� �� ���� ������
	RoadCell(int i, int j, RoadCell * nextCell = nullptr);
	// ����������� ������ � ���� ������
	~RoadCell() { delete m_nextCell; }

	// ���������� ������� ������ �� ����
	std::pair<int, int> &getCoordinates() { return m_posOnField; }

	RoadCell *getNextCell() { return m_nextCell; }
	void setNextCell(RoadCell * nextCell) { m_nextCell = nextCell; }
	RoadCell *getPrevCell() { return m_prevCell; }
	void setPrevCell(RoadCell * prevCell) { m_prevCell = prevCell; }

	BlockOnField *getBlockOnCell() { return m_blockOnCell; }
	void setBlockOnCell(BlockOnField *block) { m_blockOnCell = block; }
	
	// ��������� ����� �� ���� ������, ������� ����� �� ������ ������ ����
	Enemy * getEnemyOnCell();
	// �������� ����� �� ��� ������
	void setEnemyOnCell(Enemy * enemy) { m_enemiesOnCell.push_back(enemy); }

	// ������� ����� �� ������
	void removeEnemyFromCell(Enemy * enemy);
	// ����������, ���� �� �� ���� ����������
	bool isCellClear() { return m_enemiesOnCell.empty(); }
};