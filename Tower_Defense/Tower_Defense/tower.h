#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "consts.h"

class Missiles;
class RoadCell;

// ����� �����
class Tower
{
private:
	// ��� �����
	int m_type;
	// ��������� ���������
	int m_range{ 1 };
	// ���� �����
	double m_dmg;
	// ��������� �� ������� �����
	sf::Texture * m_towerTexture;
	// ���������� ����� �� ����
	std::pair<int, int> m_position{ -1,-1 };
	// ������ ������, �� ������� ����� �������� �����
	std::vector<RoadCell*> m_cellsInRange;
	// �������� ������ ���������
	void changeRange();
public:
	Tower(int i, int j, int type, sf::Texture * towersTextures[TOWERS_COUNT]);
	~Tower() {}

	// ��������� �����
	void drawTower();
	// �������
	void shoot(Missiles &missiles);
	// �������� ���� �����
	void changeDamage();
	// ���������, ���� ����� �������� �����
	void checkForBuffs();

	std::pair<int, int>& getPosition() { return m_position; }
	int getTowerType() const { return m_type; }
	int getRange() const { return m_range; }
};