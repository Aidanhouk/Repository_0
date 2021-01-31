#pragma once

class Enemy;
class Beam;

// класс класс последнего врага
class LastEnemy
{
private:
	// указатель на базового врага
	Enemy * m_baseEnemy;
	// лучи для эффектов
	Beam *m_beams[100];
public:
	LastEnemy(Enemy * enemy)
		: m_baseEnemy{ enemy } {}
	~LastEnemy() {}

	// создание лучей
	void createEffects();
	// передвижение лучей
	void moveEffects();
	// отрисовка лучей
	void drawEffects();
	// освобождение памяти под лучи
	void deleteEffects();
};