#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "enemy.h"

// ����� �������� �� �������
class Missiles
{
private:
	// ��������� ������ ��� ��������� ��������, ��� ����� ����� �����
	// ����������, ��� ��������� ����� (pair<int, int>)
	// � ��������� �� ������, � ������� ��� ����������� �������
	// ������ ��������� �� �������
	std::vector<std::pair<std::pair<int, int>, Enemy*>*> missilesVector;
public:
	Missiles() {}
	~Missiles() {}

	// ������������ ��� �������
	void drawMissiles(sf::RenderWindow & window);
	// ��������� ������ � ������ ��������
	void addMissile(std::pair<std::pair<int, int>, Enemy*> * missile) { missilesVector.push_back(missile); }
	// ������� ������ ��������
	void deleteMissiles();
};
