#pragma once

#include <vector>

#include "enemy.h"
#include "roadCell.h"

// �����, ����������� ������ �����������
class EnemiesWave
{
private:
	// ������� �����
	int m_level;
	// �������� ��������
	int m_enemiesLeft;
	// ��� ������� � �����
	std::vector<Enemy*> m_enemiesList;
public:
	// ��������� ����� - ������� �����
	EnemiesWave(int level);
	~EnemiesWave() {};

	// ��������� ���������� �������
	void spawnNextEnemy(RoadCell * cellToSpawn);
	// ������� ���� �����
	void nextWave();
	// ��������� ���� ������
	void drawAllEnemies(sf::RenderWindow &window);
	// �������� ������, ���� ���������� 1, �� ����� ��������
	bool moveAllEnemies();
	// ���������, ���� �� �����
	void checkAlive(int &money);

	// ���������� ������� �����
	int getLevel() const { return m_level; }
	// ���������� ���-�� ������ � �����
	int getEnemiesLeft() const { return m_enemiesLeft; }
};