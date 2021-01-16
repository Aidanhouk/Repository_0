#include "roadCell.h"

RoadCell::RoadCell(int i, int j, RoadCell * nextCell)
	:m_nextCell{ nextCell }
{
	m_posOnField.first = i;
	m_posOnField.second = j;
}