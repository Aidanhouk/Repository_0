#pragma once

#include <SFML/Graphics.hpp>

#include "roadCell.h"

// класс противника
class Enemy
{
private:
	// тип врага
	int m_type;
	// здоровье
	int m_hp;
	// сколько с него падает денег
	int m_coins;
	// в какую сторону должен двигаться
	int m_direction;
	// насколько далеко от центра клетки, нужно для отрисовки и смены ячейки
	int m_distance{ 0 };
	// на какой клетке находится
	RoadCell *m_position{ nullptr };
public:
	// в конструктор нужно передать тип монстра
	Enemy(int type);
	~Enemy() {}

	// сбрасываем m_distance и меняем клетку
	void changePosition();
	// отрисовка врага
	void drawEnemy(sf::RenderWindow &window);
	// враг двигается
	void enemyMoves() { m_distance += 2; }
	// враг получает урон
	void getDamage(int dmg) { m_hp -= dmg; }
	// рисовать получение выстрела
	void drawShot(sf::RenderWindow &window);

	// возвращает позицию врага
	RoadCell *getPositionEnemy() { return m_position; }
	// устанавливаем позицию врага
	void setPosition(RoadCell * position) { m_position = position; }
	// возвращает направление движения
	int getDirection() const { return m_direction; }
	// устанавливаем направление движения
	void setDirection(RoadCell * currentPosition);
	// получаем m_distance
	int getDistance() const { return m_distance; }
	// получаем hp
	int getHealth() const { return m_hp; }
	// получаем кол-во монет с врага
	int getCoins() const { return m_coins; }
};