#pragma once

#include <vector>

class Enemy;
class Tower;

// класс отвечает за снаряды
class Missiles
{
private:
	// вектор снарядов, указатель на башню + указатель на врага, в которого был сделан выстрел
	std::vector<std::pair<Tower*, Enemy*>*> missilesVector;
public:
	Missiles() {}
	~Missiles() {}

	// отрисовывает все снаряды
	void drawMissiles();
	// добавляет снаряд в вектор снарядов
	void addMissile(std::pair<Tower*, Enemy*> * missile) { missilesVector.push_back(missile); }
	// очищает вектор снарядов
	void deleteMissiles();
};
