#pragma once

#include <SFML/Graphics.hpp>

#include "consts.h"

class RoadCell;
class EnemiesWave;

// класс противника
class Enemy
{
protected:
	// жив ли юнит
	bool m_isAlive{ 0 };
	// убит ли юнит
	bool m_isKilled{ 0 };
	// тип врага
	int m_type;
	// уровень волны
	int m_waveLevel;
	// здоровье
	double m_hp;
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
	// волна
	EnemiesWave *m_wave;
public:
	Enemy(int type, int currentWaveLevel, sf::Texture * enemyTextures[ENEMIES_COUNT], EnemiesWave * wave);
	~Enemy() {}

	// сбрасываем m_distance и меняем клетку
	void changePosition();
	// отрисовка врага
	void drawEnemy();
	// отрисовка шкалы здоровья
	void drawHPBar();
	// враг двигается
	void enemyMoves();
	// враг получает урон, возвращает, умер ли враг
	bool getDamage(int dmg);
	// изменить скорость врага
	void changeSpeed();
	// изменить урон врага
	void changeDamage();

	RoadCell *getPositionEnemy() { return m_position; }
	void setPosition(RoadCell * position) { m_position = position; }
	
	int getDirection() const { return m_direction; }
	void setDirection(RoadCell * currentPosition);
	double getDistance() const { return m_distance; }

	int getType() const { return m_type; }
	int getCoins() const { return m_coins; }
	double getSpeed() const { return m_speed; }

	bool getIsAlive() const { return m_isAlive; }
	void setIsAlive(bool isAlive) { m_isAlive = isAlive; }
	bool getIsKilled() const { return m_isKilled; }
};