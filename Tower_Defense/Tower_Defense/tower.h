#pragma once

#include <SFML/Graphics.hpp>

#include "field.h"
#include"missilesControl.h"

// ����� �����
class Tower
{
private:
	// ��� �����
	int m_type;
	// ���� �����
	int m_dmg;
	// ���������� ����� �� ����
	std::pair<int, int> m_position{ -1,-1 };
public:
	Tower(int i, int j, int type);
	~Tower() {}

	// ��������� �����
	void drawTower(sf::RenderWindow & window);
	// �������
	void shoot(Field &field, Missiles &missiles);
};