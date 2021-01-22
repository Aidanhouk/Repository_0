#include "cycleFuncions.h"

#include <thread>

// перерыв между спавном противника?
static bool breakEnemy{ 0 };
// переменные для измерения времени между спавном следующего монстра
static std::chrono::time_point<std::chrono::steady_clock> startNextEnemy;
static std::chrono::time_point<std::chrono::steady_clock> endNextEnemy;

void spawnNextEnemyCycle(EnemiesWave &enemiesWave, Field &field)
{
	// спавн след противника
	if (!breakEnemy) {
		enemiesWave.spawnNextEnemy(field.getStartPos());
		startNextEnemy = std::chrono::high_resolution_clock::now();
		breakEnemy = 1;
	}
	// закончился ли перерыв между спавном врага?
	if (breakEnemy) {
		endNextEnemy = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> breakEnemyTime{ endNextEnemy - startNextEnemy };
		// если прошло x сек, выпускаем след врага
		if (breakEnemyTime.count() > 1) {
			breakEnemy = 0;
		}
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
		if (breakTime.count() > 1) {
			enemiesWave.nextWave();
			endOfWave = 0;
			_break = 0;
		}
	}
}