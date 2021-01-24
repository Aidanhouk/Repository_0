#pragma once

#include <vector>

class Enemy;
class BlockOnField;

// класс ячейки дороги
class RoadCell
{
private:
	// позиция клетки на поле <строка, столбец>
	std::pair<int, int> m_posOnField;
	// указатель на следующую клетку дороги
	RoadCell *m_nextCell;
	// указатель на предыдующую клетку дороги
	RoadCell *m_prevCell;
	// укзаатель на блок, который находится на этой клетке
	BlockOnField *m_blockOnCell{ nullptr };
	// вектор с указателями на врагов находящихся на этой клетке,
	std::vector<Enemy*> m_enemiesOnCell;
public:
	// принимает позиции на поле и указатель на след ячейку
	RoadCell(int i, int j, RoadCell * nextCell = nullptr);
	// освобождает память у след ячейки
	~RoadCell() { delete m_nextCell; }

	// возвращает позицию клетки на поле
	std::pair<int, int> &getCoordinates() { return m_posOnField; }

	RoadCell *getNextCell() { return m_nextCell; }
	void setNextCell(RoadCell * nextCell) { m_nextCell = nextCell; }
	RoadCell *getPrevCell() { return m_prevCell; }
	void setPrevCell(RoadCell * prevCell) { m_prevCell = prevCell; }

	BlockOnField *getBlockOnCell() { return m_blockOnCell; }
	void setBlockOnCell(BlockOnField *block) { m_blockOnCell = block; }
	
	// возращает врага на этой клетке, который встал на клетку раньше всех
	Enemy * getEnemyOnCell();
	// добавить врага на эту клетку
	void setEnemyOnCell(Enemy * enemy) { m_enemiesOnCell.push_back(enemy); }

	// удалить врага из клетки
	void removeEnemyFromCell(Enemy * enemy);
	// возвращает, есть ли на поле противники
	bool isCellClear() { return m_enemiesOnCell.empty(); }
};