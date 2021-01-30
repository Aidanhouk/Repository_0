#include "cycleFuncions.h"

#include "globals.h"
#include "enemiesWave.h"
#include "field.h"

// переменные для измерения времени между спавном следующего монстра
static sf::Clock startNextEnemy;
static sf::Clock endNextEnemy;
static float spawnBreakTimeSummary;

void resetTimeToSpawn() 
{
	startNextEnemy.restart();
}

void spawnNextEnemyCycle(EnemiesWave &enemiesWave)
{
	endNextEnemy.restart();
	float time{ startNextEnemy.getElapsedTime().asSeconds() - endNextEnemy.getElapsedTime().asSeconds() };
	spawnBreakTimeSummary += time * (1 + 2 * gameSpeed);
	// если прошла 1 сек, выпускаем след врага
	if (spawnBreakTimeSummary > 1) {
		enemiesWave.spawnNextEnemy((*field).getStartPos());
		spawnBreakTimeSummary = 0;
	}
	startNextEnemy.restart();
 }

// перерыв между волнами?
static bool _break{ 0 };
// переменные для измерения времени между волнами
static sf::Clock startWave;
static sf::Clock endWave;

void waveBreakCycle(EnemiesWave &enemiesWave, bool &endOfGame, bool &endOfWave)
{
	// если волна закончилась, запускаем таймер для перерыва
	if (!_break) {
		enemiesWave.cleanWave();
		_break = 1;
		// если игрок прошел макс уровень, игра заканчивается
		if (enemiesWave.getLevel() == enemiesWave.getMaxLevel()) {
			result = 1;
			endOfGame = 1;
			return;
		}
		startWave.restart();
	}
	// если перерыв
	if (_break) {
		endWave.restart();
		float time{ startWave.getElapsedTime().asSeconds() - endWave.getElapsedTime().asSeconds() };
		// если прошли 3 сек, начинаем следующую волну
		if (time > 3 * (1 - (float)gameSpeed / 1.5)) {
			enemiesWave.nextWave();
			endOfWave = 0;
			_break = 0;
		}
	}
}

void setToDefault()
{
	pause = 1;
	gameSpeed = 0;
	spawnBreakTimeSummary = 0;
	startNextEnemy.restart();
}