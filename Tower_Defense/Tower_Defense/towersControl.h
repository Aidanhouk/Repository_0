#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "consts.h"

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
	void drawAllTowers();
	// ����� ��������
	void towersShoot(Missiles &missiles);
	// �������� ��������� ����� ��� ��������
	void markTowerToDelete(int i, int j);
	// ������� ����� � ���� + ������� �������� �� ���������
	int deleteTower(int i, int j);
	// �������� ���� �����
	void changeTowersDamage();
	// ���������, ���� �� ����� �����-����
	void checkTowersForBuffs();
};