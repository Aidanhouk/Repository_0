#pragma once

#include <SFML/Graphics.hpp>

#include "roadCell.h"

// ����� ����
class Field
{
private:
	// ����
	int **m_field;
	// ��������� �� ��������� ������ ������ (�� �����)
	RoadCell *m_startCell;
	// ��������� �� �������� ������ ������
	RoadCell *m_finishCell;
	// ������ ����� ������
	//std::list<RoadCell*> m_roadCells;
public:
	Field();
	~Field();

	// �������� ������ � ������ �� �����������
	void addCell(int i, int j);
	// ������� ������ ��� ��������
	void makeRoad();
	// ������ ������
	void paintRoad(sf::RenderWindow &window);
	// ���������, �������� �� ��� ������
	int getCellValue(int i, int j) const { return m_field[i][j]; }
	// ���� � ������ ��������� �����, ����� ��� �������������
	int &getCell(int i, int j) { return m_field[i][j]; }

	// ���������� ��������� �������
	RoadCell * getStartPos() { return m_startCell; }
	// ���������� �������� ������
	RoadCell * getFinishPos() { return m_finishCell; }
	// ���������� ��������� �� ����
	int** getField() const { return m_field; }
};