#pragma once

#include <SFML/Graphics.hpp>

#include "field.h"
#include "missilesControl.h"

// ����� �����
class Tower
{
private:
	// ��� �����
	int m_type;
	// ���� �����
	int m_dmg;
	// ��������� �� ������� �����
	sf::Texture * m_towerTexture;
	// ���������� ����� �� ����
	std::pair<int, int> m_position{ -1,-1 };
public:
	Tower(int i, int j, int type, sf::Texture * towersTextures[TOWERS_COUNT]);
	~Tower() {}

	// ��������� �����
	void drawTower(sf::RenderWindow & window);
	// �������
	void shoot(Field &field, Missiles &missiles);
};