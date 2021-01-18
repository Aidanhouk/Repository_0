#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "enemy.h"

// класс отвечает за снаряды
class Missiles
{
private:
	// принимает вектор для отрисовки снарядов, для этого нужно знать
	// координаты, где находится башня (pair<int, int>)
	// и указатель на клетку, в которую был осуществлен выстрел
	// хранит указатели на снаряды
	std::vector<std::pair<std::pair<int, int>, Enemy*>*> missilesVector;
public:
	Missiles() {}
	~Missiles() {}

	// отрисовывает все снаряды
	void drawMissiles(sf::RenderWindow & window);
	// добавляет снаряд в вектор снарядов
	void addMissile(std::pair<std::pair<int, int>, Enemy*> * missile) { missilesVector.push_back(missile); }
	// очищает вектор снарядов
	void deleteMissiles();
};
