#include "cycleFuncions.h"

#include <thread>

#include "enemiesWave.h"
#include "field.h"

// переменные для измерения времени между спавном следующего монстра
static std::chrono::time_point<std::chrono::steady_clock> startNextEnemy = std::chrono::high_resolution_clock::now();
static std::chrono::time_point<std::chrono::steady_clock> endNextEnemy;

void spawnNextEnemyCycle(EnemiesWave &enemiesWave, Field &field)
{
	endNextEnemy = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> breakEnemyTime{ endNextEnemy - startNextEnemy };
	// если прошло x сек, выпускаем след врага
	if (breakEnemyTime.count() > 1) {
		enemiesWave.spawnNextEnemy(field.getStartPos());
		startNextEnemy = std::chrono::high_resolution_clock::now();
	}
}

// перерыв между волнами?
static bool _break{ 0 };
// переменные для измерения времени между волнами
static std::chrono::time_point<std::chrono::steady_clock> startWave;
static std::chrono::time_point<std::chrono::steady_clock> endWave;

void waveBreakCycle(EnemiesWave &enemiesWave, int &result, bool &endOfGame, bool &endOfWave)
{
	// если волна закончилась, запускаем таймер для перерыва
	if (!_break) {
		enemiesWave.cleanWave();
		// если игрок прошел макс уровень, игра заканчивается
		if (enemiesWave.getLevel() == enemiesWave.getMaxLevel()) {
			result = 1;
			endOfGame = 1;
		}
		startWave = std::chrono::high_resolution_clock::now();
		_break = 1;
	}
	// если перерыв
	if (_break) {
		endWave = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> breakTime{ endWave - startWave };
		// если прошло x сек, начинаем следующую волну
		if (breakTime.count() > 2) {
			enemiesWave.nextWave();
			endOfWave = 0;
			_break = 0;
		}
	}
}