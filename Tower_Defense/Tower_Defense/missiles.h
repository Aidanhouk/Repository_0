#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Enemy;
class Tower;

// ����� �������� �� �������
class Missiles
{
private:
	// ������ ��������, ��������� �� ����� + ��������� �� �����, � �������� ��� ������ �������
	std::vector<std::pair<Tower*, Enemy*>*> missilesVector;
public:
	Missiles() {}
	~Missiles() {}

	// ������������ ��� �������
	void drawMissiles(sf::RenderWindow & window);
	// ��������� ������ � ������ ��������
	void addMissile(std::pair<Tower*, Enemy*> * missile) { missilesVector.push_back(missile); }
	// ������� ������ ��������
	void deleteMissiles();
};
