#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "consts.h"

class Enemy;
class RoadCell;

// �����, ����������� ������ �����������
class EnemiesWave
{
private:
	// ������� �����
	int m_level;
	// ���� ������� �����
	const int m_maxLevel;
	// �������� ��������
	int m_enemiesLeft;
	// ��� ������� � �����
	std::vector<Enemy*> m_enemiesList;
	// ������� ������
	sf::Texture* m_enemiesTextures[ENEMIES_COUNT]{ nullptr };
public:
	// ��������� ����� - ������� �����
	EnemiesWave(int level, int maxLevel);
	~EnemiesWave();

	// ��������� ���������� �������
	void spawnNextEnemy(RoadCell * cellToSpawn);
	// ������� ������ �� �����
	void cleanWave();
	// ������� ���� �����
	void nextWave();
	// ��������� ���� ������
	void drawAllEnemies(sf::RenderWindow &window);
	// �������� ������, ���� ���������� 1, �� ����� ��������
	bool moveAllEnemies();
	// ��������� ����-�� ����������� �� 1
	void reduceEnemiesLeft() { --m_enemiesLeft; }
	// �������� �������� ������������ ������
	void changeEnemiesSpeed();
	// �������� ���� ������
	void changeEnemiesDamage();

	int getLevel() const { return m_level; }
	int getMaxLevel() const { return m_maxLevel; }
	int getEnemiesLeft() const { return m_enemiesLeft; }
};