#pragma once

#include <vector>

#include "tower.h"
class Field;
class Missiles;

// �����, �������������� ��� �����
class TowersControl
{
private:
	// ��� �����
	std::vector<Tower*> m_towersList;
public:
	TowersControl() {}
	~TowersControl();

	// ��������� �����
	void addTower(int i, int j, int type);
	// ���������� ��� �����
	void drawAllTowers(sf::RenderWindow &window);
	// ����� ��������
	void towersShoot(Field & field, Missiles &missiles);
};