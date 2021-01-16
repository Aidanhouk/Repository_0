#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "roadCell.h"

// ����� ����
class Field
{
private:
	// ����
	int **m_field;
	// ������ ����� ������
	std::list<RoadCell*> m_roadCells;
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
	RoadCell * getStartPos() { return m_roadCells.front(); }
	// ���������� ������ ����� ������
	std::list<RoadCell*> & getRoad() { return m_roadCells; }
	// ���������� ��������� �� ����
	int** getField() const { return m_field; }
};