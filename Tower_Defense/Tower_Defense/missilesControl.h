#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "enemy.h"

class Missiles
{
private:
	// ��������� ������ ��� ��������� ��������, ��� ����� ����� �����
	// ����������, ��� ��������� ����� (pair<int, int>)
	// � ��������� �� ������, � ������� ��� ����������� �������
	// ������ ��������� �� �������
	std::vector<std::pair<std::pair<int, int>, RoadCell*>*> missilesVector;
public:
	Missiles() {}
	~Missiles() {}

	// ������������ ��� �������
	void drawMissiles(sf::RenderWindow & window);
	// ��������� ������ � ������ ��������
	void addMissile(std::pair<std::pair<int, int>, RoadCell*> * missile);
	// ������� ������ ��������
	void deleteMissiles();
};
