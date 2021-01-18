#pragma once

#include <utility>
class Enemy;

// класс ячейки дороги
class RoadCell
{
private:
	// позиция клетки на поле
	std::pair<int, int> m_posOnField;
	// указатель на следующую клетку дороги
	RoadCell *m_nextCell;
	// указатель на предыдующую клетку дороги
	RoadCell *m_prevCell;
	// тут можно сделать вектор с указателями на врагов находящихся на этой клетке,
	// но в этой версии игры на 1 клетке может стоять только 1 враг
	Enemy *m_enemyOnCell{ nullptr };
	// кол-во врагов на этом поле
	int m_countEnemiesOnCell;
public:
	// принимает позиции на поле и указатель на след ячейку
	RoadCell(int i, int j, RoadCell * nextCell = nullptr);
	// освобождает память у след ячейки
	~RoadCell() { delete m_nextCell; }

	// возвращает позицию клетки на поле
	std::pair<int, int> &getCoordinates() { return m_posOnField; }

	// возвращает m_nextCell
	RoadCell *getNextCell() { return m_nextCell; }
	// установить m_nextCell
	void setNextCell(RoadCell * nextCell) { m_nextCell = nextCell; }
	
	// возвращает m_prevCell
	RoadCell *getPrevCell() { return m_prevCell; }
	// установить m_prevCell
	void setPrevCell(RoadCell * prevCell) { m_prevCell = prevCell; }
	
	// возращает врага на этой клетке
	Enemy * getEnemyOnCell() { return m_enemyOnCell; }
	// установить врага на эту клетку
	void setEnemyOnCell(Enemy * enemy) { m_enemyOnCell = enemy; }
};