#pragma once

#include <SFML/Graphics.hpp>

#include "roadCell.h"

// ����� ����������
class Enemy
{
private:
	// ��� �����
	int m_type;
	// ��������
	int m_hp;
	// ������� � ���� ������ �����
	int m_coins;
	// � ����� ������� ������ ���������
	int m_direction;
	// ��������� ������ �� ������ ������, ����� ��� ��������� � ����� ������
	int m_distance{ 0 };
	// �� ����� ������ ���������
	RoadCell *m_position{ nullptr };
public:
	// � ����������� ����� �������� ��� �������
	Enemy(int type);
	~Enemy() {}

	// ���������� m_distance � ������ ������
	void changePosition();
	// ��������� �����
	void drawEnemy(sf::RenderWindow &window);
	// ���� ���������
	void enemyMoves() { m_distance += 2; }
	// ���� �������� ����
	void getDamage(int dmg) { m_hp -= dmg; }
	// �������� ��������� ��������
	void drawShot(sf::RenderWindow &window);

	// ���������� ������� �����
	RoadCell *getPositionEnemy() { return m_position; }
	// ������������� ������� �����
	void setPosition(RoadCell * position) { m_position = position; }
	// ���������� ����������� ��������
	int getDirection() const { return m_direction; }
	// ������������� ����������� ��������
	void setDirection(RoadCell * currentPosition);
	// �������� m_distance
	int getDistance() const { return m_distance; }
	// �������� hp
	int getHealth() const { return m_hp; }
	// �������� ���-�� ����� � �����
	int getCoins() const { return m_coins; }
};