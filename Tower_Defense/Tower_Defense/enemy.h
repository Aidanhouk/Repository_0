#pragma once

#include <SFML/Graphics.hpp>

#include "consts.h"

class RoadCell;

// класс противника
class Enemy
{
private:
	// жив ли юнит
	bool m_isAlive{ 0 };
	// убит ли юнит
	bool m_isKilled{ 0 };
	// тип врага
	int m_type;
	// уровень волны
	int m_waveLevel;
	// здоровье
	int m_hp;
	// сколько с него падает денег
	int m_coins;
	// урон
	int m_dmg;
	// в какую сторону должен двигаться
	int m_direction;
	// насколько далеко от центра клетки, нужно для отрисовки и смены ячейки
	double m_distance{ 0 };
	// скорость движения
	double m_speed;
	// указатель на тестуру врага
	sf::Texture * m_enemyTexture;
	// на какой клетке находится
	RoadCell *m_position{ nullptr };
public:
	// в конструктор нужно передать тип монстра
	Enemy(int type, int level, sf::Texture * enemyTextures[ENEMIES_COUNT]);
	~Enemy() {}

	// сбрасываем m_distance и меняем клетку
	void changePosition();
	// отрисовка врага
	void drawEnemy(sf::RenderWindow &window);
	// отрисовка шкалы здоровья
	void drawHPBar(sf::RenderWindow &window);
	// враг двигается
	void enemyMoves();
	// враг получает урон
	void getDamage(int dmg) { m_hp -= dmg; }

	// возвращает позицию врага
	RoadCell *getPositionEnemy() { return m_position; }
	// устанавливаем позицию врага
	void setPosition(RoadCell * position) { m_position = position; }
	// возвращает направление движения
	int getDirection() const { return m_direction; }
	// устанавливаем направление движения
	void setDirection(RoadCell * currentPosition);
	// получаем m_distance
	double getDistance() const { return m_distance; }
	// получаем hp
	int getHealth() const { return m_hp; }
	// получаем кол-во монет с врага
	int getCoins() const { return m_coins; }
	// получаем m_isAlive
	bool getIsAlive() const { return m_isAlive; }
	// устанавливаем m_isAlive
	void setIsAlive(bool isAlive) { m_isAlive = isAlive; }
	// получаем m_isKilled
	bool getIsKilled() const { return m_isKilled; }
	// устанавливаем m_isKilled
	void setIsKilled(bool isKilled) { m_isKilled = isKilled; }
};