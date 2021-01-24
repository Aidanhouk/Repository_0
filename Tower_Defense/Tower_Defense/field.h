#pragma once

#include <SFML/Graphics.hpp>

class RoadCell;

// ����� ����
class Field
{
private:
	// �������/�����
	int m_level;
	// ����
	int **m_field;
	// ��������� �� ��������� ������ ������ (�� �����)
	RoadCell *m_startCell{ nullptr };
	// ��������� �� �������� ������ ������
	RoadCell *m_finishCell{ nullptr };
	// �������� ������
	sf::Texture *m_roadTexture;
	// �������� ������
	sf::Texture *m_finishLineTexture;
public:
	Field(int level);
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

	RoadCell * getStartPos() { return m_startCell; }
	RoadCell * getFinishPos() { return m_finishCell; }
	// ���������� ��������� �� ����
	int** getField() const { return m_field; }
};