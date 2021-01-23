#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "consts.h"

class Field;
class Missiles;
class Tower;

// �����, �������������� ��� �����
class TowersControl
{
private:
	// ��� �����
	std::vector<Tower*> m_towersList;
	// ������� �����
	sf::Texture* m_towersTextures[TOWERS_COUNT]{ nullptr };
public:
	TowersControl();
	~TowersControl();

	// ��������� �����
	void addTower(int i, int j, int type);
	// ���������� ��� �����
	void drawAllTowers(sf::RenderWindow &window);
	// ����� ��������
	void towersShoot(Field & field, Missiles &missiles);
};